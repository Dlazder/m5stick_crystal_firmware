// PID::IR_TV_B_GONE

#ifdef IR_USE_RMT
// ── RMT-based (internal HAL) — TV-B-Gone for M5StickS3 ──
#include "../../hal/irRmtHal.h"

// irRmtHal.h already provides: UNK=0, NEC=1, SONY=2, SAM=3, RC5=4
// irTvBGoneCodes.h expects these additional IRremote protocol names:
constexpr uint8_t SAMSUNG   = SAM;   // 3
constexpr uint8_t RC6       = 5;
constexpr uint8_t PANASONIC = 6;
constexpr uint8_t SHARP     = 7;
constexpr uint8_t DENON     = 8;
constexpr uint8_t JVC       = 9;
constexpr uint8_t KASEIKYO  = 10;
constexpr uint8_t ONKYO     = 11;

#include "irTvBGoneCodes.h"

static int  tvbIndex = 0;
static bool tvbRunning = false;
static bool tvbDone = false;

// Map TV-B-Gone protocol ID → irproto. Returns UNK if not supported.
static irproto _tvbToIrproto(uint8_t p) {
    switch (p) {
        case NEC:       return NEC;
        case SONY:      return SONY;
        case SAMSUNG:   return SAM;
        case RC5:       return RC5;
        default:        return UNK;
    }
}

void _tvbSendCurrent() {
    const TvbCode& c = TVB_CODES[tvbIndex];
    irproto p = _tvbToIrproto(c.protocol);
    if (p == UNK) {
        Serial.printf("TVB [%d/%d] unsupported protocol %d, skip\n",
            tvbIndex + 1, TVB_COUNT, c.protocol);
        return;
    }
    uint32_t code;
    uint8_t  bits;
    if (p == SONY) {
        bits = c.bits ? c.bits : 12;
        code = c.command;  // SONY: command only
    } else if (p == RC5) {
        bits = 14;  // RC5: 1 start + 1 toggle + 5 address + 6 command = 13? Actually 14 bits
        code = ((uint32_t)c.address << 6) | c.command;
    } else {
        bits = 32;
        code = c.address | ((uint32_t)c.command << 8);
    }
    sendIR(p, code, bits, 1, 1);
    Serial.printf("TVB [%d/%d] %s addr=0x%04X cmd=0x%04X\n",
        tvbIndex + 1, TVB_COUNT,
        proto[p].name, c.address, c.command);
}

void irTvBGoneLoop() {
    if (isSetup()) {
        tvbIndex = 0;
        tvbRunning = false;
        tvbDone = false;
        M5.Power.setExtOutput(true, m5::ext_none);
        centeredPrint("TV-B-Gone", MEDIUM_TEXT, true);
        drawHintCustom("enter: start", "A: start");
    }

    if (tvbDone) { checkExit(); return; }

    if (isBtnAWasPressed() || isKbEnterPressed()) {
        if (tvbRunning) {
            tvbRunning = false;
            centeredPrint("TV-B-Gone", MEDIUM_TEXT, true);
            drawHintCustom("enter: start", "A: start");
        } else {
            tvbIndex = 0;
            tvbRunning = true;
            updateTimer();
        }
    }

    if (tvbRunning && checkTimer(100)) {
        _tvbSendCurrent();
        String progress = String(tvbIndex + 1) + " / " + String(TVB_COUNT);
        String lines[] = { "TV-B-Gone", progress };
        centeredPrintRows(lines, 2, MEDIUM_TEXT, true);
        drawHintCustom("enter: stop", "A: stop");
        tvbIndex++;
        if (tvbIndex >= TVB_COUNT) {
            tvbRunning = false;
            tvbDone = true;
            soundSuccess();
            String lines2[] = { "TV-B-Gone", L->TXT_IR_TVB_DONE };
            centeredPrintRows(lines2, 2, MEDIUM_TEXT);
        }
        updateTimer();
    }

    if (checkExit()) {
        tvbRunning = false;
        tvbDone = false;
    }
}

#else
// ── GPIO-based (IRremote) for other boards ──
#include <IRremote.hpp>
#include "irTvBGoneCodes.h"

static int  tvbIndex = 0;
static bool tvbRunning = false;
static bool tvbDone = false;

void _tvbSendCurrent() {
    const TvbCode& c = TVB_CODES[tvbIndex];
    switch (c.protocol) {
        case NEC:       IrSender.sendNEC(c.address, c.command, 0);                   break;
        case SAMSUNG:   IrSender.sendSamsung(c.address, c.command, 0);               break;
        case SONY:      IrSender.sendSony(c.address, c.command, 0, c.bits);          break;
        case RC5:       IrSender.sendRC5(c.address, c.command, 0);                   break;
        case RC6:       IrSender.sendRC6(c.address, c.command, 0);                   break;
        case LG:        IrSender.sendLG(c.address, c.command, 0);                    break;
        case PANASONIC: IrSender.sendPanasonic(c.address, c.command, 0);             break;
        case KASEIKYO:  IrSender.sendKaseikyo(c.address, c.command, 0, 0);           break;
        case DENON:     IrSender.sendDenon(c.address, c.command, 0);                 break;
        case SHARP:     IrSender.sendSharp(c.address, c.command, 0);                 break;
        case JVC:       IrSender.sendJVC((uint8_t)c.address, (uint8_t)c.command, 0); break;
        case ONKYO:     IrSender.sendOnkyo(c.address, c.command, 0);                 break;
        default: break;
    }
    Serial.printf("TVB [%d/%d] %s addr=0x%04X cmd=0x%04X\n",
        tvbIndex + 1, TVB_COUNT,
        getProtocolString((decode_type_t)c.protocol), c.address, c.command);
}

void irTvBGoneLoop() {
    if (isSetup()) {
        tvbIndex = 0;
        tvbRunning = false;
        tvbDone = false;
        IrSender.begin(irTxPin);
        centeredPrint("TV-B-Gone", MEDIUM_TEXT, true);
        drawHintCustom("enter: start", "A: start");
    }

    if (tvbDone) { checkExit(); return; }

    if (isBtnAWasPressed() || isKbEnterPressed()) {
        if (tvbRunning) {
            tvbRunning = false;
            centeredPrint("TV-B-Gone", MEDIUM_TEXT, true);
            drawHintCustom("enter: start", "A: start");
        } else {
            tvbIndex = 0;
            tvbRunning = true;
            updateTimer();
        }
    }

    if (tvbRunning && checkTimer(100)) {
        _tvbSendCurrent();
        String progress = String(tvbIndex + 1) + " / " + String(TVB_COUNT);
        String lines[] = { "TV-B-Gone", progress };
        centeredPrintRows(lines, 2, MEDIUM_TEXT, true);
        drawHintCustom("enter: stop", "A: stop");
        tvbIndex++;
        if (tvbIndex >= TVB_COUNT) {
            tvbRunning = false;
            tvbDone = true;
            soundSuccess();
            String lines2[] = { "TV-B-Gone", L->TXT_IR_TVB_DONE };
            centeredPrintRows(lines2, 2, MEDIUM_TEXT);
        }
        updateTimer();
    }

    if (checkExit()) {
        tvbRunning = false;
        tvbDone = false;
    }
}
#endif // IR_USE_RMT

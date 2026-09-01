// Executes a single command line, writing any response to `out`.
// Lines that don't start with '/' are ignored, so raw UART traffic passes through untouched.
void handleSerialCommandLine(String cmd, Print& out) {
  // Check the raw line before trimming: indented output (e.g. the help text)
  // starts with a space, so it is never re-read as a command when UART RX is
  // looped back to TX.
  if (!cmd.startsWith("/")) return;

  cmd.trim();

  if (cmd == "/screenshot") {
    screenshotCommand(out);
  } else if (cmd == "/info") {
    infoCommand(out);
  } else if (cmd == "/help") {
    helpCommand(out);
  } else if (cmd == "/shutdown") {
    shutdownCommand(out);
  } else {
    out.println("Command not found!");
  }
}

// Reads one line from `port` and hands it to handleSerialCommandLine.
void handleSerialCommands(Stream& port) {
  if (!port.available()) return;

  String cmd = port.readStringUntil('\n');
  handleSerialCommandLine(cmd, port);
}

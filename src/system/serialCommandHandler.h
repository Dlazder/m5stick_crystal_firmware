// Executes a single command line, writing any response to `out`.
// Lines that don't start with '/' are ignored, so raw UART traffic passes through untouched.
void handleSerialCommandLine(String cmd, Print& out) {
  cmd.trim();
  if (!cmd.startsWith("/")) return;

  if (cmd == "/screenshot") {
    screenshotCommand(out);
  } else if (cmd == "/info") {
    infoCommand(out);
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

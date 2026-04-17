# ------------------------------------------------
# Arduino Library Makefile (Ubuntu + Arduino CLI)
# ------------------------------------------------

BOARD      = arduino:avr:uno
OUTPUT_DIR = build
EXAMPLES   = $(wildcard examples/*/*.ino)
ARDUINO_CLI = arduino-cli

all: compile

compile:
	@mkdir -p $(OUTPUT_DIR)
	@for sketch in $(EXAMPLES); do \
		name=$$(basename $$sketch .ino); \
		echo "\n==> Compiling example: $$name"; \
		$(ARDUINO_CLI) compile --fqbn $(BOARD) \
			--build-path $(OUTPUT_DIR)/$$name \
			--libraries $(PWD) \
			$$sketch || exit 1; \
	done
	@echo "\n✅ Compilation successful for all examples!"

clean:
	rm -rf $(OUTPUT_DIR)
	@echo "🧹 Clean complete."

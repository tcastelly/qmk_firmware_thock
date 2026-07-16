# Thock shares the ONE canonical users/tcy brain (mounted at /qmk_firmware/shared_tcy
# by build-conundrum-tcy.sh), bridged onto this frozen base by tcy_compat.h.

TAP_DANCE_ENABLE = yes

# board rules.mk disables this; needed for the _ESC layer mouse keys
# (KC_MS_* movement + the KC_WH_* wheel keys, which were silently dead)
MOUSEKEY_ENABLE = yes

# common.mk defaults MOUSE_SHARED_EP to yes, which prepends a report_id byte
# to report_mouse_t — but the arm_atsam USB stack uses a dedicated mouse
# endpoint whose 5-byte descriptor has NO report id, and send_mouse() memcpys
# the struct raw. With the id byte in, every field lands one byte off on the
# host (x read as y, y read as wheel). report.h only undefs MOUSE_SHARED_EP
# for arm_atsam inside its NKRO block, and this build has NKRO off.
MOUSE_SHARED_EP = no

# headers (tcy.h / tapdance.h) live in the mounted canonical dir; the keymap
# dir provides the keymap_introspection.h stand-in that tcy.c includes
CFLAGS += -Ishared_tcy
CFLAGS += -Ikeyboards/thock/conundrum/keymaps/tcy

# Compile the canonical tcy.c / tapdance.c via thin wrappers that apply the
# adapter after QMK headers (see tcy_wrap.c / tapdance_wrap.c). The wrappers
# #include the unmodified canonical sources from shared_tcy/.
SRC += keyboards/thock/conundrum/keymaps/tcy/tcy_wrap.c
SRC += keyboards/thock/conundrum/keymaps/tcy/tapdance_wrap.c

# no console on the thock tcy build (keeps i2c scan out)
CONSOLE_ENABLE = no

# thock has no pointing device: skip the CPI init in tcy.c keyboard_post_init
OPT_DEFS += -DTCY_DISABLE_CPI_INIT

# Full canonical tap-dance set (same as the EC boards get from users/tcy/rules.mk):
# enables the real TD_A / TD_RALT / TD_LGUI / TD_LOWER actions and the
# _NUM_PADS / _ACCENTS_RALT layers. Without this, TD_A is a no-op stub and the
# 'a' key (and the RALT thumb) does nothing. The two extra layers are defined
# in this keymap (transparent placeholders) so the layer_on() lookups are valid.
OPT_DEFS += -DTCY_FULL_TD

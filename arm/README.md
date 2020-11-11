# Simple Bootloader Based on STM32-P103

Here have two examples of bootloader that based on STM32-P103.

# Requirements
- ARM Toolchain(arm-none-eabi)
- QEMU(qemu-system-arm)

## Example 1

Example 1 runs the bootloader at power on, then loads and executes the app from the bootloader.

More details see the [Example 1](/example_1/README.md).

## Example 2

Example 2 is based on example 1, which extends the function that bootloader can send a config to the app.

More details see the [Example 2](/example_2/README.md).

# Debug Tips

See the [how-to debug](/Debug.md).

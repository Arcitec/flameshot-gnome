# Flameshot-GNOME

A drop-in replacement for the Flameshot binary, making it fully compatible with
GNOME's keyboard shortcuts, and automatically adapting itself to Wayland or X11.

Anytime you would call `flameshot`, just call `flameshot-gnome` instead!


### Requirements

Building:

- `gcc` (GNU C Compiler)

Running:

- `flameshot` (The Flameshot binary itself must *also* be installed natively on
  the machine and exist in `$PATH`. No containers/sandboxes such as Flatpak!
  The Flameshot-GNOME launcher automatically runs the original Flameshot binary
  in a way that makes GNOME happy.)


### Installation

Install:

```sh
./install.sh
```

Uninstall:

```sh
./install.sh -u
```


### Creating a GNOME Keyboard Shortcut for Flameshot

- Open **GNOME Settings.**
- Go to the **"Keyboard"** section.
- Click on **"Keyboard Shortcuts: View and Customize Shortcuts".**
- Click on **"Custom Shortcuts".**
- Click the **"+"** symbol to add a new shortcut.
- Set **"Name"** to `Screenshot`.
- Set **"Command"** to `flameshot-gnome gui`.
- Set **"Shortcut"** to anything you want (**Super + Shift + S** is popular).
- Have fun!

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
- You have now created a shortcut which brings up Flameshot's interactive GUI
  for capturing and annotating screenshots.
- Tip: GNOME has a built-in shortcut for capturing the entire screen, which
  always saves the images as huge PNG files and spams your notifications with
  new screenshot alerts. If you just want a shortcut that immediately captures
  the whole screen and saves it using Flameshot's default image compression
  settings (the "Preferred save file extension" in `flameshot-gnome config`),
  you can achieve that by creating another shortcut with the following command:
  `flameshot-gnome screen -p '/home/yourname/Pictures/Screenshots'`. You can
  use any path you want, but must manually create the directory if it's missing.
  You can name this shortcut `Screenshot (Full, Direct Save)`, with the hotkey
  **Shift + PrintScreen.**
- Tip: There are many other command-line Flameshot features which you can use for
  automating your screenshots. To see the available options, append `--help` to
  a Flameshot command and read the documentation, such as
  `flameshot-gnome gui --help` or `flameshot-gnome screen --help`.
- Have fun!


### Giving Screenshot Permissions to Flameshot on GNOME

- The first time you take a screenshot with Flameshot on Wayland, GNOME will ask
  if you really want to share your screen with the application. Say yes.
- GNOME 43 and above will remember the screenshot portal permission for every
  application, so that you only have to say yes once.
- The permission dialog will automatically appear the first time you use the
  custom Flameshot keyboard shortcut (see above), but you can also try running
  the `flameshot-gnome gui` command manually in a Terminal to force it to appear.
- Tip: If you've ever said "No" during the first permission dialog, GNOME seems
  to remember "Flameshot has no permissions" forever. A user has provided some
  [instructions](https://github.com/flameshot-org/flameshot/issues/2868#issuecomment-1384310540)
  for a script that resets the screenshot permissions, if you need to try again.

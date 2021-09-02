# Installing Fonts

Copy the Folders in this directory, i.e. the fonts/ directory, to `~/.fonts` directory.

Then run this command in a terminal:
```bash
sudo fc-cache -f -v
```

And check whether the required fonts are installed by:
```bash
fc-list | grep -i "Noto\|Fira"
```

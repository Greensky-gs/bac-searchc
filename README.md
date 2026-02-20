# Bac-searchc

Yet another tool for my bac scrapper results, written in **C** this time

## Usage

1. Download source ( `git clone https://github.com/Greensky-gs/bac-searchc` for instance )
2. Download **gcc** if not done ( `pacman -S gcc --noconfirm` or something )
3. Download **make** to use the makefile if you want (you can manually compile using only gcc though) : `pacman -S make --noconfirm`, or anything similar
4. Create executable : `make` if you have, manually if you did it without make.
5. You might need to create a `./path.txt` file containing the path to the result file you got from the scrapper
6. Execute the file : located at `./build/main.exe` by default
7. I think there is no command helper, so use `clear` to clear the screen, and `search --name first_name --prenom name` (both -- are optional)

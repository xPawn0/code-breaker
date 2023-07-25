# Current Features:

* Command-Line Interface "CLI": Usage and help commands.
* Creating a copy file. (optional)

# Future Features:

* [ ] ~Check program version and suggest update if there is newer. (optional)~ This is just more work for nothing useful nor rewarding
* [ ] Costum extension for copied files. (optional, default=".cbcp")
* [X] **[HEAVY, LIGHT]** injection modes:
    * **HEAVY**: zwsp-byte after each character in the file. **file size: _(fsize x 3 + fsize)_**
    * **LIGHT**: zwsp-byte at random locations in the file. **file size: _(fsize/10 x 3 + fsize)_**

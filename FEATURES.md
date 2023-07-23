# Current Features:

* Command-Line Interface "CLI": Usage and help commands.
* Creating a copy file. (optional)

# Future Features:

* Check program version and suggest update if there is newer. (optional)
* Costum extension for copied files. (optional, default=".cbcp")
* **[HEAVY, LIGHT]** injection modes:
    * **HEAVY**: zwsp-byte after each character in the file. **file size: _(fsize*3+fsize)_**
    * **LIGHT**: zwsp-byte at the beggening, center and the end of the file. **file size: _(3*3+fsize)_**

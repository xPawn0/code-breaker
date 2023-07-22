# Ɔ0DE BЯEAK3R - cbreaker

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

#### This program is for educational purposes only, and is not meant to be used in any harmful form.

code-breaker or _('cbreaker')_ is a [**ZWSP**](https://en.wikipedia.org/wiki/Zero-width_space) ("zero-width space") injector to inject source code _(or files in general)_ with zero-width bytes everywhere in the file, leading the source code to not work properly, and to make it harder for the developer to maintance the issue in his code, just like a beautiful prank to pull up on your programmer friends xD.
<center>This idea was inspired by the <a href="https://github.com/Microsoft/vscode/issues/58252">issue</a> in the <a href="https://en.wikipedia.org/wiki/Visual_Studio_Code">Visual Studio Code IDE</a></center>

## Table of Contents

- [Install](#install)
	- [Build](#build)
	- [Play](#play)
	- [Delete](#remove)
- [Usage](#usage)
- [Related Efforts](#related-efforts)
- [Maintainers](#maintainers)
- [Contributing](#contributing)
- [License](#license)

## Install

This project uses [gcc](https://gcc.gnu.org/) and [make](https://www.gnu.org/software/make/). Go check them out if you don't have them locally installed.

### Installation:
```sh
$ git clone https://github.com/xPawn0/code-breaker/
$ cd code-breaker/
```
#### Build:
```sh
code-breaker/:$ make  #defaults to build
code-breaker/:$ make binary  #build & create binary as `cbreaker` in (~/.local/bin)
```
#### Play:
```sh
code-breaker/:$ make run  #only display usage (Discouraged)
code-breaker/:$ ./bin/code-breaker  #or cbreaker
```
#### Remove:
```sh
code-breaker/:$ make remove
```

## Usage

```sh
$ ./code-breaker
Usage: code-breaker -f infile [options]

    -h, --help        show this help message and exit

General options
    -f, --file=<str>  File to inject
    -c, --copy        Make a copy of the original file. (extension:'.cbcp')
```

## Maintainers

Author [@xPawn0](https://github.com/xPawn0)

## Contributing

Feel free to dive in! [Open an issue](https://github.com/xPawn0/code-breaker/issues/new) or submit PRs.

Standard Readme follows the [Contributor Covenant](http://contributor-covenant.org/version/1/3/0/) Code of Conduct.

### Contributors

This project exists thanks to all the people who <a href="https://github.com/xPawn0/code-breaker/graphs/contributors">contributed</a>.


## License

[MIT](LICENSE.txt) © 2023 xPawn0

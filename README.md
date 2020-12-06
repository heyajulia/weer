# weer

**weer** is a tiny CLI weather app that is under active development.

It can currently determine your approximate location using your IP address and
print a detailed weather forecast (in JSON format) to stdout.

## Installation

### Docker

#### Build it yourself

```bash
docker build -f Dockerfile.mini -t weer:mini .
docker run --rm weer:mini
```

#### Download a pre-built Docker image

```bash
docker run --rm heyajulia-docker-weer-docker.bintray.io/weer/weer:mini
```

### Native executables

I'm working on building native executables for a number of platforms (macOS,
Linux, and — hopefully! — Windows).

## Development

### Build

1. Clone the repository (or download a ZIP file)
2. Install Make, Clang, and cURL.
3. Run `make`.

### Auto-format code

Run `make fmt` to automatically format all C source files and headers. This
requires `clang-format` to be installed.

### Debugging memory issues

The `dev` image comes pre-loaded with everything you need to work on
**weer**. I use it to debug memory issues, because Valgrind isn't supported on
macOS.

This image is pretty big (~1 GB), and you probably don't need it.

You can download a pre-built image directly from **weer**'s Bintray Docker
registry:

```bash
docker run --rm -v $PWD:/cwd -it heyajulia-docker-weer-docker.bintray.io/weer/weer:dev bash
```

or build it yourself:

```bash
docker build -f Dockerfile.dev -t weer:dev .
docker run --rm -v $PWD:/cwd -it weer:dev bash
```

## Quick links

- [Using Locationforecast][lf]: detailed information about how a Yr client
  should behave.
- [Data access and terms of service][tos]: general information and the required
  branding.

[lf]: https://developer.yr.no/doc/locationforecast/HowTO/
[tos]: https://hjelp.yr.no/hc/en-us/articles/360001946134-Data-access-and-terms-of-service

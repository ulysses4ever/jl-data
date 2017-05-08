using Logging

Logging.configure(output=STDOUT, level=Logging.INFO)

# For now just have the build script tell the user to add fox to their path.
# Later it could try adding it to /usr/local/bin or a user directory on the path if they
# exist.

Logging.info(
    "A script for test automation with julia playgrounds is located in deps/usr/bin/fox.\n" *
    "If you would like to make your script callable from anywhere please add \n" *
    "deps/usr/bin to your path or symlink it into a folder already on your path such\n" *
    "a local bin directory."
)

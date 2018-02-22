#ifndef __OPTIONS_INCLUDED__
#define __OPTIONS_INCLUDED__

typedef struct ConfigOpts {
    int sflag, rflag, dflag, vflag, iflag, pflag;
    int optind;
    char *fname;
} ConfigOpts;

ConfigOpts *getOptions(int argc, char **argv);
void getFilename(ConfigOpts *config, int argc, char **argv);

#endif // options.h

/* key.h */

int KeyParseChallenge(const char *challenge, 
                      int *algorithm, int *sequence, char *seed);

int KeyGenerateResponse(int algorithm, int sequence, const char *seed, 
                        const char *password, char *response);

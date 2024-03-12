#ifndef LOGGER_H
#define LOGGER_H

#define LOG(x) printf("%s\n", x);
#define LOG_DEBUG(x) printf("%s:%d: %s\n", __func__, __LINE__, x);

#endif

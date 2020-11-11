#ifndef _CONFIG_H_
#define _CONFIG_H_

struct version {
	unsigned int major;
	unsigned int minor;
	unsigned int build;
};

struct boot_config {
  struct version bootloader_version;
  char message[64];
  unsigned int checksum;
};

#endif /* _CONFIG_H_ */
#ifndef __AESMI_VERSION_H_
#define __AESMI_VERSION_H_

#define _STR(x) _VAL(x)  // 第一级传递参数
#define _VAL(x) #x       // 第二级字符串化

#define AESMI_VERSION_NUMBER  \
	((AESMI_MAJOR)*0x1000000 + (AESMI_MINOR)*0x10000 + (AESMI_PATCH)*0x100 + AESMI_BUILD)

#define AESMI_VERSION_STR "v" \
	_STR(AESMI_MAJOR) "." \
	_STR(AESMI_MINOR) "." \
	_STR(AESMI_PATCH) "." \
	_STR(AESMI_BUILD)

#endif // __AESMI_VERSION_H_

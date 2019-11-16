ifeq ($(strip $(DEVKITPRO)),)
$(error "Please set DEVKITPRO in your environment. export DEVKITPRO=<path to>/devkitpro")
endif

include $(DEVKITPRO)/gloat/gloat_rules

TARGET		:=	opengl

dist:
	mkdir -p include/GL
	cp glcorearb.h include/GL
	cp glext.h include/GL
	@tar --exclude=*~ -cjf lib$(TARGET).tar.bz2 include
	rm -rf include

clean:
	rm -rf include lib$(TARGET).tar.bz2

install:
	mkdir -p $(DESTDIR)$(PORTLIBS)
	bzip2 -cd lib$(TARGET).tar.bz2 | tar -xf - -C $(DESTDIR)$(PORTLIBS)
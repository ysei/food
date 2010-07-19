TARGET=food

ifeq ($(shell hostname), stolni-lampicka)
    QMAKE=/usr/local/Trolltech/Qt-4.5.3/bin/qmake
else
	QMAKE=qmake
endif

build:
	cd src && $(QMAKE) -project -o $(TARGET).PRO && $(QMAKE)
	make -C src

run:
	src/$(TARGET)

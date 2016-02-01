unix {
    isEmpty(target.path) {
        linux-rasp-pi-g++ {
            target.path = /home/pi/$${TARGET}/bin
            launcher.files = launcher.sh
            launcher.path = /home/pi/$${TARGET}/bin
        INSTALLS += launcher
        }
    }
}

INSTALLS += target
export(INSTALLS)

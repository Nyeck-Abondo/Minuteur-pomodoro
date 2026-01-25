#include "../../include/sound.h"

namespace App {
    namespace Sound {
        
        sound::sound(std::filesystem::path alarm, std::filesystem::path notifdone, std::filesystem::path notifbegin, std::filesystem::path notifEnd, std::filesystem::path endTonality)
                    : m_alarm(alarm), m_notificationDoneTonality(notifdone), m_notificationBeginTonality(notifbegin), m_notificationEndTonality(notifEnd), m_EndPomodoro(endTonality) {
            std::cout << "🔊 module de son créé !!" << std::endl;
        }

        /**
         *  @name Playsound
         * 
         * @param tonality
         * @brief joue le son chargé en mémoire
         */
        void sound::Playsound(sf::Music tonality) {
            //lecture du son
            tonality.play();
            //verification du status de la musique
            if (tonality.getStatus() == sf::Music::Status::Playing) {
                sf::sleep(sf::milliseconds(100));
            }
        }

    } // namespace sound  
} // namespace App

#pragma once

#include "../libs/SFML/Audio.hpp"
#include <iostream>

namespace App {
    namespace Sound {

        struct sound {
        sf::Music m_alarm;
        sf::Music m_notificationDoneTonality;
        sf::Music m_notificationBeginTonality;
        sf::Music m_notificationEndTonality;
        sf::Music m_EndPomodoro;

        //counstructeurs et destructeurs
        sound(std::filesystem::path alarm, std::filesystem::path notifdone, std::filesystem::path notifbegin
                , std::filesystem::path notifEnd, std::filesystem::path endTonality);

        //METODES DE LA STRUCTURE
        void Playsound(sf::Music tonality);
        };

    } // namespace Sound
} // namespace App
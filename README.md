# Игра "Catch the Dot" / Игра "Споймай точку"

## Правила / Rules

### Русский
На светодиодной ленте бегает огонек белого цвета туда-сюда. И есть игровой светодиод синего цвета, который появляется в случайном месте. Задача — нажать на любую кнопку на клавиатуре в терминале в то время, когда бегающий светодиод и игровой светодиод окажутся в одной точке. Если попал, то получаешь одно очко, и скорость бегущего светодиода замедляется. Если не попал, то очко получает компьютер, и скорость бегущего светодиода увеличивается. Счет отображается в терминале после каждой игры.

### English
A white light runs back and forth on an LED strip. There is also a blue game LED that appears in a random location. The goal is to press any key on the keyboard in the terminal when the running LED and the game LED are at the same point. If you succeed, you earn one point, and the speed of the running LED slows down. If you miss, the computer earns a point, and the speed of the running LED increases. The score is displayed in the terminal after each round.

## Не реализовано / Not yet implemented

### Русский
1. Таймаут игры (к примеру, 3 секунды), за которые нужно уложиться и споймать бегающий светодиод, иначе засчитывается проигрыш раунда.
2. Общее число раундов, после которых считается, что ты окончательно выиграл игру.
3. Вывод единицы на выход микроконтроллера в случае выигрыша для подключения внешних исполнительных устройств (замков, сейфов, выдачи конфет и так далее).

### English
1. A game timeout (e.g., 3 seconds) within which you must catch the running LED; otherwise, the round is counted as a loss.
2. A total number of rounds after which you are considered to have won the game.
3. Outputting a high signal from the microcontroller in case of a win to connect external devices (locks, safes, candy dispensers, etc.).
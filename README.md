Исходные данные на псевдо - языке ассемблера загружаются в программу из текстового файла. 
Чтение команд из файла.
Чтение команд из файла построчно, удаление ненужных символов, таких как лишние пробелы и переносы строк. Разделение строк на части (команды и операнды).
Метки (например, loop_start:) используются для переходов в программе. Их адреса (индексы в списке команд) сохраняются отдельно.
Преобразование команд в числовые коды:
Для каждой команды определяется опкод команды, исходя из опкодов команд в map.
Преобразование операндов:
Регистры заменяются на их числовые коды из map.
Косвенная адресация (например, [rax]) преобразуется с добавлением смещения 100.
Непосредственные значения (например, 5) преобразуются с добавлением смещения 170.
Метки заменяются на их адреса из словаря.
Если операнд отсутствует, он заменяется на специальный код NONE_OPCODE (255).
Сохранение результата:
Машинные инструкции записываются в файл и дублируются на консоль.

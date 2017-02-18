
#ifndef WORD_H_
#define WORD_H_

class Word
{
private:
    int n;  // Количество битов
    bool * bits; // Указатель на массив битов
    int k;  // Количество контрольных разрядов
    char * str; // Указатель на сторку для вывода
public:
    Word(const char * s, int k = 0);   	// Получает строку из '1' и '0'. Так же каоличество контрольных разрядов
    Word();								// Конструктор по умолчанию
    Word(int n, int k = 0);				// Получает количество битов и количество контрольных разрядов
    Word(const Word & w);				// Опреатор копирования
    ~Word();							// Дестроктор

    bool operator>(const Word & w) const;
    bool operator>=(const Word & w) const;
    bool operator==(const Word & w) const;
    bool operator!=(const Word & w) const { return !(*this == w); }
    bool operator<=(const Word & w) const;
    bool operator<(const Word & w) const;

    Word operator+(const Word & w) const;
    Word & operator+=(const Word & w);

    Word & operator=(const Word & w);
    Word operator>>(int I) const;  	// Циклический сдвиг вправо
    Word & operator>>=(int I); 		// Циклический сдвиг вправо
    Word operator<<(int I) const;	// Циклический сдвиг влево
    Word & operator<<=(int I);		// Циклический сдвиг влево

    Word & leftShift(int i);		// Циклический влево
    Word & rightShift(int i);		// Циклический вправо

    bool operator[](int i) const;
    bool & operator[](int i);
    char * to_char();
    int weight() const;					// Количество единиц в слове
    void print(bool set = false) const; // Вывод слова. Если переданн true, выводится также значения для n и k.
    int len() const { return n; }
    bool set(int i);					// Установить i-ый бит в 1
    bool reset(int i);					// Установтиь i-ый бит в 0
    void set();							// Установить все биты в 1
    void reset();						// Установить все биты в 0
    int max() const;
};

#endif /* WORD_H_ */

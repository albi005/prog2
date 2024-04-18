/**
 * \file ciphers.h
 *
 * Ezt a fájlt be kell adni (fel kell tölteni) a megoldással.
 */

#ifndef CipherS_H
#define CipherS_H

#include <string>
#include <vector>

#include "memtrace.h"

/**
 * Az ős osztály interfésze
 */
class Cipher {
  public:
    /**
     * Titkosítja a kapott stringet
     * @param   message titkosítandó üzenet
     * @return  a message szöveg titkosított változata
     */
    virtual std::string encode(const std::string& message) const = 0;
    /**
     * Dekódolja a kapott stringet
     * @param   ciphertext titkosított üzenet
     * @return  a megfejtett nyílt szöveg
     */
    virtual std::string decode(const std::string& ciphertext) const = 0;
    /**
     * Létrehoz egy másolatot dinamikusan
     * @return  a létrehozott objektumra mutató pointer
     */
    virtual Cipher* clone() const = 0;

    virtual ~Cipher(){};
};

class ShiftCipher : public Cipher {
  public:
    std::string encode(const std::string& message) const;
    std::string decode(const std::string& ciphertext) const;

  protected:
    virtual int getShift(char indexFromA, size_t index) const = 0;

  private:
    char encodeChar(char c, size_t index, bool invert) const;
    std::string encode(const std::string& s, bool invert) const;
};

class CaesarCipher : public ShiftCipher {
    int shift;

  public:
    CaesarCipher(int shift) : shift(shift) {}
    Cipher* clone() const;

  protected:
    virtual int getShift(char indexFromA, size_t index) const;
};

class MyCipher : public ShiftCipher {
    std::string key;
    int offset;

  public:
    MyCipher(std::string key) : MyCipher(key, 0) {}
    MyCipher(std::string key, int offset) : key(key), offset(offset) {}
    Cipher* clone() const;

  protected:
    virtual int getShift(char indexFromA, size_t index) const;
};

class CipherQueue : public Cipher {
    size_t len = 0;
    Cipher** pData = NULL;

  public:
    CipherQueue() {}
    CipherQueue(CipherQueue const&);
    void add(Cipher* cipher);
    std::string encode(const std::string& message) const;
    std::string decode(const std::string& ciphertext) const;
    Cipher* clone() const;
    ~CipherQueue();
};

#endif

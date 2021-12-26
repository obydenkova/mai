#ifndef _DOCUMENT_H_
#define _DOCUMENT_H_

#include <fstream>
#include <cstdint>
#include <memory>
#include <string>
#include <algorithm>
#include "figure.h"
#include <vector>
#include "factory.h"

struct document {
public:
    void Print() const ;
    document(std::string& newName): name_(newName), factory_(), buffer_(0) {};
    void Insert(std::shared_ptr<figure>& ptr);
    void Rename(const std::string& newName);
    void Save(const std::string& filename) const;
    void Load(const std::string& filename);
    std::shared_ptr<figure> GetFigure(uint32_t index);
    void Erase(uint32_t index);
    std::string GetName();
    size_t Size();
private:
    friend class InsertCommand;
    friend class DeleteCommand;
    factory factory_;
    std::string name_;
    std::vector<std::shared_ptr<figure>> buffer_;
    void RemoveLast();
    void InsertIndex(std::shared_ptr<figure>& newFigure, uint32_t index);
};


#endif //_DOCUMENT_H_

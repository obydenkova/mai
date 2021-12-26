#ifndef _D_EDITOR_H_
#define _D_EDITOR_H_

#include "figure.h"
#include "document.h"
#include <stack>
#include "command.h"

struct editor {
private:
    std::shared_ptr<document> doc_;
    std::stack<std::shared_ptr<Acommand>> history_;
public:
    ~editor() = default;
    void PrintDocument();
    void CreateDocument(std::string& newName);
    bool DocumentExist();
    editor() : doc_(nullptr), history_() {}
    void InsertInDocument(std::shared_ptr<figure>& newFigure);
    void DeleteInDocument(uint32_t index);
    void SaveDocument();
    void LoadDocument(std::string& name);
    void Undo();
};

#endif // _D_EDITOR_H_

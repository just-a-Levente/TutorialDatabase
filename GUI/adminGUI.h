//
// Created by lkovacs on 5/15/25.
//

#ifndef ADMINGUI_H
#define ADMINGUI_H

#include <QtWidgets>
#include "../Services/admin_service.h"

class AdminGUI : public QWidget {
    Q_OBJECT

public:
    explicit AdminGUI(AdminService& ctrl, QWidget* parent = nullptr);
    ~AdminGUI() override;

private:
    QVBoxLayout* mainLayout;
    QWidget* inputWidget;
    QHBoxLayout* inputLayout;
    QListWidget* tutorialList;

    QWidget* fieldWidget;
    QFormLayout* fieldLayout;

    QLabel* linkLabel;
    QLineEdit* linkField;
    QLabel* titleLabel;
    QLineEdit* titleField;
    QLabel* presenterLabel;
    QLineEdit* presenterField;
    QLabel* minutesLabel;
    QLineEdit* minutesField;
    QLabel* secondsLabel;
    QLineEdit* secondsField;
    QLabel* numberOfLikesLabel;
    QLineEdit* numberOfLikesField;
    QLabel* errorLabel;

    QWidget* buttonWidget;
    QVBoxLayout* buttonLayout;

    QPushButton* addButton;
    QPushButton* removeButton;
    QPushButton* updateButton;

    QHBoxLayout* undoRedoLayout;
    QPushButton* undoButton;
    QPushButton* redoButton;
    QLabel* errorUndoLabel;

    QAction* undoAction;
    QAction* redoAction;

    AdminService& controller;

    void init();
    void connectSignalsAndSlots();
    void handleAddOperation() const;
    void handleRemoveOperation() const;
    void handleUpdateOperation() const;
    void handleUpdateTutorialList() const;
    void handleUndo() const;
    void handleRedo() const;
};

#endif //ADMINGUI_H

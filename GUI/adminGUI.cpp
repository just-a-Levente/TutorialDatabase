//
// Created by lkovacs on 5/15/25.
//

#include "../Exceptions/exceptions.h"
#include "../Validator/TutorialValidator.h"
#include <iostream>
#include "adminGUI.h"

AdminGUI::AdminGUI(AdminService &ctrl, QWidget *parent) : QWidget(parent, Qt::Window), controller(ctrl) {
    init();
    connectSignalsAndSlots();
    setAttribute(Qt::WA_DeleteOnClose);
}

AdminGUI::~AdminGUI() {
    parentWidget()->show();
    delete &controller;
}

void AdminGUI::init() {
    setWindowTitle("Admin");
    const auto screen = QApplication::primaryScreen();
    auto rect = screen->geometry();
    int height = 500;
    int width = 1000;
    rect.setHeight(height);
    rect.setWidth(width);
    setGeometry(rect);

    /*
     * The code block below initializes this widget's and its children's layout:
     *
     * +----------------------------------------+
     * |              inputWidget               |
     * +----------------------------------------+     |  whole window managed
     * |       errorLabel (hidden at first)     |     |  by mainLayout
     * +----------------------------------------+     V
     * |              tutorialList              |
     * +----------------------------------------+
     */
    this->mainLayout = new QVBoxLayout{};
    this->inputWidget = new QWidget{};
    this->errorLabel = new QLabel{"This shouldn't be seen!"};
    this->tutorialList = new QListWidget{};
    this->mainLayout->addWidget(this->inputWidget);
    this->mainLayout->addWidget(this->errorLabel);
    this->mainLayout->addWidget(this->tutorialList);
    this->setLayout(mainLayout);

    /*
     * The code block below initializes the inputWidget's and its children's layout:
     *
     * +--------------------+-------------------+
     * |                    |                   |
     * |    fieldWidget     |    buttonWidget   |
     * |                    |                   |
     * +--------------------+-------------------+
     *                  -------->
     *              inputWidget managed
     *                  by inputLayout
     */
    this->inputLayout = new QHBoxLayout{};
    this->fieldWidget = new QWidget{};
    this->buttonWidget = new QWidget{};
    this->inputLayout->addWidget(this->fieldWidget);
    this->inputLayout->addWidget(this->buttonWidget);
    this->inputWidget->setLayout(this->inputLayout);

    // Initializing the input fields and adding them to fieldLayout
    // (that is specifically a QFormLayout - it will just hold the
    // input fields row by row
    this->fieldLayout = new QFormLayout{};

    this->linkField = new QLineEdit{};
    this->linkLabel = new QLabel{"&Link:"};
    this->linkLabel->setBuddy(this->linkField);

    this->titleField = new QLineEdit{};
    this->titleLabel = new QLabel{"&Title:"};
    this->titleLabel->setBuddy(this->titleField);

    this->presenterField = new QLineEdit{};
    this->presenterLabel = new QLabel{"&Presenter:"};
    this->presenterLabel->setBuddy(this->presenterField);

    this->minutesField = new QLineEdit{};
    this->minutesLabel = new QLabel{"&Minutes:"};
    this->minutesLabel->setBuddy(this->minutesField);

    this->secondsField = new QLineEdit{};
    this->secondsLabel = new QLabel{"&Seconds:"};
    this->secondsLabel->setBuddy(this->secondsField);

    this->numberOfLikesField = new QLineEdit{};
    this->numberOfLikesLabel = new QLabel{"&Number of likes:"};
    this->numberOfLikesLabel->setBuddy(this->numberOfLikesField);

    this->fieldLayout->addRow(this->linkLabel, this->linkField);
    this->fieldLayout->addRow(this->titleLabel, this->titleField);
    this->fieldLayout->addRow(this->presenterLabel, this->presenterField);
    this->fieldLayout->addRow(this->minutesLabel, this->minutesField);
    this->fieldLayout->addRow(this->secondsLabel, this->secondsField);
    this->fieldLayout->addRow(this->numberOfLikesLabel, this->numberOfLikesField);
    this->fieldWidget->setLayout(this->fieldLayout);

    // Initializing the buttons and adding them to buttonLayout - so that
    // inside the buttonWidget the buttons come one after another downwards
    this->buttonLayout = new QVBoxLayout{};
    this->addButton = new QPushButton{"Add"};
    this->removeButton = new QPushButton{"Remove"};
    this->updateButton = new QPushButton{"Update"};
    this->buttonLayout->addWidget(this->addButton);
    this->buttonLayout->addWidget(this->removeButton);
    this->buttonLayout->addWidget(this->updateButton);
    this->buttonWidget->setLayout(this->buttonLayout);

    // Hiding the errorLabel at initialization since we don't have any errors yet
    this->errorLabel->hide();
    this->mainLayout->setAlignment(this->errorLabel, Qt::AlignCenter);

    undoRedoLayout = new QHBoxLayout;
    mainLayout->addLayout(undoRedoLayout);
    undoButton = new QPushButton{"Undo"};
    redoButton = new QPushButton{"Redo"};
    undoRedoLayout->addWidget(undoButton);
    undoRedoLayout->addWidget(redoButton);

    errorUndoLabel = new QLabel;
    mainLayout->addWidget(errorUndoLabel);
    errorUndoLabel->hide();

    undoAction = new QAction{this};
    redoAction = new QAction{this};
    undoAction->setShortcut(QKeySequence::Undo);
    redoAction->setShortcut(QKeySequence::Redo);
    this->addAction(undoAction);
    this->addAction(redoAction);

    // Loading in the repository's contents
    this->handleUpdateTutorialList();
}

void AdminGUI::connectSignalsAndSlots() {
    connect(this->addButton, &QPushButton::clicked, this, &AdminGUI::handleAddOperation);
    connect(this->removeButton, &QPushButton::clicked, this, &AdminGUI::handleRemoveOperation);
    connect(this->updateButton, &QPushButton::clicked, this, &AdminGUI::handleUpdateOperation);
    connect(undoButton, &QPushButton::clicked, this, &AdminGUI::handleUndo);
    connect(redoButton, &QPushButton::clicked, this, &AdminGUI::handleRedo);
    connect(undoAction, &QAction::triggered, this, &AdminGUI::handleUndo);
    connect(redoAction, &QAction::triggered, this, &AdminGUI::handleRedo);
}

void AdminGUI::handleAddOperation() const {
    const string link = this->linkField->text().toStdString();
    const string title = this->titleField->text().toStdString();
    const string presenter = this->presenterField->text().toStdString();
    const string minutes = this->minutesField->text().toStdString();
    const string seconds = this->secondsField->text().toStdString();
    const string likes = this->numberOfLikesField->text().toStdString();
    vector dataPoints{link, title, presenter, minutes, seconds, likes};

    try {
        TutorialValidator::validateDataPoints(dataPoints);

        const t_duration duration{std::stoul(minutes), std::stoul(seconds)};
        const unsigned int numberOfLikes = std::stoul(likes);

        const Tutorial newTutorial{link, title, presenter, duration, numberOfLikes};
        this->controller.addTutorialToDatabase(newTutorial);
        this->handleUpdateTutorialList();
        this->errorLabel->hide();
        this->errorUndoLabel->hide();
    } catch (TutorialValidationException const& excep) {
        this->errorLabel->setText(QString::fromStdString(excep.what()));
        this->errorLabel->show();
    } catch (TutorialWithSameLinkException const& excep) {
        this->errorLabel->setText(QString::fromStdString(excep.what()));
        this->errorLabel->show();
    }
}

void AdminGUI::handleRemoveOperation() const {
    const string link = this->linkField->text().toStdString();
    const Tutorial dummyTutorialToRemove(link, "", "", t_duration{0, 0});

    try {
        this->controller.removeTutorialFromDatabase(dummyTutorialToRemove);
        this->handleUpdateTutorialList();
        this->errorLabel->hide();
        this->errorUndoLabel->hide();
    } catch (TutorialNotFoundException const& excep) {
        this->errorLabel->setText(QString::fromStdString(excep.what()));
        this->errorLabel->show();
    }
}

void AdminGUI::handleUpdateOperation() const {
    const string link = this->linkField->text().toStdString();
    const string title = this->titleField->text().toStdString();
    const string presenter = this->presenterField->text().toStdString();
    const string minutes = this->minutesField->text().toStdString();
    const string seconds = this->secondsField->text().toStdString();
    const string likes = this->numberOfLikesField->text().toStdString();
    vector dataPoints{link, title, presenter, minutes, seconds, likes};

    try {
        TutorialValidator::validateDataPoints(dataPoints);

        const t_duration duration{std::stoul(minutes), std::stoul(seconds)};
        const unsigned int numberOfLikes = std::stoul(likes);

        const Tutorial updatedTutorial{link, title, presenter, duration, numberOfLikes};
        this->controller.updateTutorialInDatabase(updatedTutorial);
        this->handleUpdateTutorialList();
        this->errorLabel->hide();
        this->errorUndoLabel->hide();
    } catch (TutorialValidationException const& excep) {
        this->errorLabel->setText(QString::fromStdString(excep.what()));
        this->errorLabel->show();
    } catch (TutorialNotFoundException const& excep) {
        this->errorLabel->setText(QString::fromStdString(excep.what()));
        this->errorLabel->show();
    }
}

void AdminGUI::handleUpdateTutorialList() const {
    this->tutorialList->clear();
    vector<Tutorial> tutorials = this->controller.returnContentsOfDatabase();

    for (auto& tutorial : tutorials)
        this->tutorialList->addItem(QString::fromStdString(tutorial.toString()));
}

void AdminGUI::handleUndo() const {
    try {
        controller.undoOperation();
        this->handleUpdateTutorialList();
        errorUndoLabel->hide();
    } catch (UndoRedoException const& excep) {
        this->errorUndoLabel->setText(QString::fromStdString(excep.what()));
        this->errorUndoLabel->show();
    }
}

void AdminGUI::handleRedo() const {
    try {
        controller.redoOperation();
        this->handleUpdateTutorialList();
        errorUndoLabel->hide();
    } catch (UndoRedoException const& excep) {
        this->errorUndoLabel->setText(QString::fromStdString(excep.what()));
        this->errorUndoLabel->show();
    }
}

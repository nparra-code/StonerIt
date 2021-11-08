#include "sonerit.h"
#include "ui_sonerit.h"

sonerit::sonerit(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::sonerit)
{
    ui->setupUi(this);

    start = new QGraphicsScene(this);
    end = new QGraphicsScene(this);
    QImage imgS(BCKGS), imgE(BCKGE);

    start->setBackgroundBrush(imgS);
    end->setBackgroundBrush(imgE);
    ui->graphicsView->setScene(start);
    activeScene = 0;

    scene1 = new QGraphicsScene(this);
    scene2 = new QGraphicsScene(this);
    scene3 = new QGraphicsScene(this);
    scene4 = new QGraphicsScene(this);
    scene5 = new QGraphicsScene(this);

    std::ifstream inFile;
    inFile.open(DATA);

    std::string data;
    inFile >> data;

    std::string temp="";
    for(unsigned long long i=0;i<=data.length();i++){
        if(data[i]!=','&&data[i]!=';') temp+=data[i];
        else if(data[i]==','||data[i]==';'){
            gameInfo.push_back(temp);
            temp="";
        }
    }
    inFile.close();

    if(gameInfo.size()==4 || gameInfo.size()==6) ui->continue_button->setDisabled(false);
    else ui->continue_button->setDisabled(true);

    ui->lcd_points->display(points);
    ui->lcd_time->display(timeLeft);

    ui->graphicsView->setSceneRect(0,0,1250,1000);

    checkStart = new QTimer(this);
    connect(checkStart,SIGNAL(timeout()),this,SLOT(checkScndPly()));
    checkStart->start(1);

    timerEnemyMov = new QTimer(this);
    connect(timerEnemyMov,SIGNAL(timeout()),this,SLOT(moveEnemies()));

    timerMov = new QTimer(this);
    connect(timerMov,SIGNAL(timeout()),this,SLOT(move()));

    timerLive = new QTimer(this);
    connect(timerLive,SIGNAL(timeout()),this,SLOT(checkStatus()));

    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(enemyShoot()));

    timerTimeLeft = new QTimer(this);
    connect(timerTimeLeft,SIGNAL(timeout()),this,SLOT(timerCount()));

    ui->label_llt->hide();
    ui->lcd_llt->hide();
}

sonerit::~sonerit()
{
    delete ui;
}

void sonerit::changeScene()
{

    switch (activeScene){
        case 0:{
            shootingTime=5000;
            mapa map1 = mapa(MAP_1,scene1,&blocksVector,&enemies,70);
            saveGame();
            ui->graphicsView->setScene(scene1);
            createHero();
            activeEnemies = enemies;
            enemiesHealth.clear();
            for(unsigned long long h=0;h<enemies.size();h++){
                enemiesHealth.push_back(enemy1.getHealth());
            }
            activeScene = 1;
            activeBrushBullet = map1.getBrushBullet();

        }
            break;
        case 1:{
            shootingTime=4000;
            blocksVector.~vector();
            mapa map2 = mapa(MAP_2,scene2,&blocksVectorChief,&enemies2,100);
            saveGame();
            ui->graphicsView->setScene(scene2);
            createHero();
            activeEnemies = enemies2;
            activeBrushBullet = map2.getBrushBullet();
            activeScene = 2;
            enemiesHealth.clear();
            for(unsigned long long h=0;h<enemies2.size();h++){
                enemiesHealth.push_back(enemy2.getHealth());
                enemies2.at(h)->setPos(1100,300);
            }
        }
            break;
        case 2:{
            shootingTime=3000;
            mapa map3 = mapa(MAP_3,scene3,&blocksVector3,&enemies3,70);
            saveGame();
            ui->graphicsView->setScene(scene3);
            createHero();
            activeEnemies = enemies3;
            activeBrushBullet = map3.getBrushBullet();
            activeScene = 3;
            enemiesHealth.clear();
            for(unsigned long long h=0;h<enemies3.size();h++){
                enemiesHealth.push_back(enemy3.getHealth());
            }
        }
            break;
        case 3:{
            blocksVector3.~vector();
            shootingTime=2000;
            mapa map4 = mapa(MAP_4,scene4,&enemies4,150);
            saveGame();
            ui->graphicsView->setScene(scene4);
            createHero();
            activeEnemies = enemies4;
            activeBrushBullet = map4.getBrushBullet();
            activeScene = 4;
            enemiesHealth.clear();
            for(unsigned long long h=0;h<enemies4.size();h++){
                enemiesHealth.push_back(enemy4.getHealth());
                enemies4.at(h)->setPos(1000,500);
            }
        }
            break;
        case 4:{
            shootingTime=1000;
            mapa map5 = mapa(MAP_5,scene5,&enemies5,200);
            ui->label_llt->show();
            ui->lcd_llt->show();
            saveGame();
            ui->graphicsView->setScene(scene5);
            createHero();
            activeEnemies = enemies5;
            activeBrushBullet = map5.getBrushBullet();
            activeScene = 5;
            enemiesHealth.clear();
            for(unsigned long long h=0;h<enemies5.size();h++){
                enemiesHealth.push_back(enemy5.getHealth());
                enemies5.at(h)->setPos(800,375);
            }
        }
            break;
        case 5:{
            std::ofstream of;
            of.open(DATA);
            of.close();
            ui->graphicsView->setScene(end);
            activeScene = 6;
            stopTimers();
        }
            break;
    }
    timerTimeLeft->stop();
    points+=timeLeft;
    timeLeft=oTime;
    timerTimeLeft->start(1000);
    timer->stop();
    timer->start(shootingTime);
}

void sonerit::move(){
    h1->setPos(h1XPOS,h1YPOS);
    heroS->setPos(h1XPOS,h1YPOS);
    if(secondHeroExists){
        h2->setPos(h2XPOS,h2YPOS);
        heroS2->setPos(h2XPOS,h2YPOS);
    }

}

void sonerit::moveEnemies(){
    if(activeScene==1) enemy1.moveEnemies1(enemies);
    if(activeScene==2) enemy2.moveEnemie2(enemies2);
    if(activeScene==3) enemy3.moveEnemies3(enemies3);
    if(activeScene==4) enemy4.moveEnemie4(enemies4);
    if(activeScene==5) enemy5.moveEnemie5(enemies5);

}

void sonerit::enemyShoot(){
    for(auto enm:activeEnemies){
        QGraphicsItem* temp = ui->graphicsView->scene()->addEllipse(0,0,30,30,QPen(Qt::transparent),activeBrushBullet);
        temp->setPos(enm->x(),enm->y());
        bullets.push_back(temp);
    }
    timerM  = new QTimer(this);
    connect(timerM,SIGNAL(timeout()),this,SLOT(moveBullet()));
    timerM->start(bulletTime);

}

void sonerit::moveBullet(){
    const int movSpeed = 7;
    if(secondHeroExists){
        for(auto bull:bullets){
            if(bull->collidesWithItem(h1)||bull->collidesWithItem(h2)||detectCollision(bull)||(bull->x())<=(100)){
                if(bull->collidesWithItem(h1)){
                    heroHealth1-=enmArray[activeScene-1].getDamage();
                }
                if(bull->collidesWithItem(h2)){
                    heroHealth2-=enmArray[activeScene-1].getDamage();
                }
                ui->graphicsView->scene()->removeItem(bull);
                if(bull->collidesWithItem(h1)||bull->collidesWithItem(h2)||detectCollision(bull)){
                    for (unsigned long long ind=0;ind<bullets.size();ind++){
                        if(bullets.at(ind)==bull){
                            bullets.erase(bullets.cbegin()+ind);
                            if(bullets.size()==0) timerM->stop();
                            break;
                        }
                    }
                }
                if((bull->x())<=(100)){
                    for (unsigned long long ind=0;ind<bullets.size();ind++){
                        ui->graphicsView->scene()->removeItem(bullets.at(ind));
                    }
                    bullets.clear();
                    timerM->stop();
                }
            }
            else bull->setPos(bull->x()-movSpeed,bull->y());
        }
    }
    else{
        for(auto bull:bullets){
            if(bull->collidesWithItem(h1)||detectCollision(bull)||(bull->x())<=(100)){
                if(bull->collidesWithItem(h1)){
                    heroHealth1-=enmArray[activeScene-1].getDamage();
                }
                ui->graphicsView->scene()->removeItem(bull);
                if(bull->collidesWithItem(h1)||detectCollision(bull)){
                    for (unsigned long long ind=0;ind<bullets.size();ind++){
                        if(bullets.at(ind)==bull){
                            bullets.erase(bullets.cbegin()+ind);
                            if(bullets.size()==0) timerM->stop();
                            break;
                        }
                    }
                }
                if((bull->x())<=(100)){
                    for (unsigned long long ind=0;ind<bullets.size();ind++){
                        ui->graphicsView->scene()->removeItem(bullets.at(ind));
                    }
                    bullets.clear();
                    timerM->stop();
                }
            }
            else bull->setPos(bull->x()-movSpeed,bull->y());
        }
    }
}

void sonerit::keyPressEvent(QKeyEvent *event){
    int movingSpace = 7;
    if(event->key()==Qt::Key_E&&(hero1Bullet.size()==0)&&h1->isEnabled())
        createHero1Bullet();
    if(event->key()==Qt::Key_U&&(hero2Bullet.size()==0)&&h2->isEnabled())
        createHero2Bullet();
    if(event->key()==Qt::Key_A&&h1->isEnabled()){
        h1XPOS-=movingSpace;
        heroS->changeDirection(210);
        direction1='l';
        if(detectCollision(h1)) h1XPOS+=2*movingSpace;
    }
    if(event->key()==Qt::Key_W&&h1->isEnabled()){
        h1YPOS-=movingSpace;
        heroS->changeDirection(140);
        direction1='u';
        if(detectCollision(h1)) h1YPOS+=2*movingSpace;
    }
    if(event->key()==Qt::Key_D&&h1->isEnabled()){
        h1XPOS+=movingSpace;
        heroS->changeDirection(70);
        direction1='r';
        if(detectCollision(h1)) h1XPOS-=2*movingSpace;
    }
    if(event->key()==Qt::Key_S&&h1->isEnabled()){
        h1YPOS+=movingSpace;
        heroS->changeDirection(0);
        direction1='d';
        if(detectCollision(h1)) h1YPOS-=2*movingSpace;
    }
    if(event->key()==Qt::Key_J&&secondHeroExists&&h2->isEnabled()){
        h2XPOS-=movingSpace;
        heroS2->changeDirection(210);
        direction1='l';
        if(detectCollision(h2)) h2XPOS+=2*movingSpace;
    }
    if(event->key()==Qt::Key_I&&secondHeroExists&&h2->isEnabled()){
        h2YPOS-=movingSpace;
        heroS2->changeDirection(140);
        direction1='u';
        if(detectCollision(h2)) h2YPOS+=2*movingSpace;
    }
    if(event->key()==Qt::Key_L&&secondHeroExists&&h2->isEnabled()){
        h2XPOS+=movingSpace;
        heroS2->changeDirection(70);
        direction1='r';
        if(detectCollision(h2)) h2XPOS-=2*movingSpace;
    }
    if(event->key()==Qt::Key_K&&secondHeroExists&&h2->isEnabled()){
        h2YPOS+=movingSpace;
        heroS2->changeDirection(0);
        direction1='d';
        if(detectCollision(h2)) h2YPOS-=2*movingSpace;
    }
    switch (event->key()) {

    case Qt::Key_X:{
        changeScene();
    }
        break;
    }
}

bool sonerit::detectCollision(QGraphicsItem* object){
        if(activeScene==1){
            for(auto block:blocksVector){
                if(object->collidesWithItem(block)){
                    return true;
                }
            }
        }
        else if(activeScene==2||activeScene==4||activeScene==5){
           for(auto block:blocksVectorChief){
                if(object->collidesWithItem(block)){
                    return true;
                }
            }
        }
        else if(activeScene==3){
            for(auto block:blocksVector3){
                if(object->collidesWithItem(block)){
                    return true;
                }
            }
        }
    return false;
}

bool sonerit::detectBulletCollision(std::list<QGraphicsRectItem*>* ls){
    for(auto bu:*ls){
        if(activeScene==1){
            for(auto block:blocksVector){
                if(bu->collidesWithItem(block)){
                    return true;
                }
            }
        }
        else if(activeScene==2||activeScene==4||activeScene==5){
            for(auto block:blocksVectorChief){
                if(bu->collidesWithItem(block)){
                    return true;
                }
            }
        }
        else if(activeScene==3){
            for(auto block:blocksVector3){
                if(bu->collidesWithItem(block)){
                    return true;
                }
            }
        }
    }
    return false;
}

bool sonerit::bullCollToEnm(std::list<QGraphicsRectItem*> ls){
    int i=0;
    for(auto bull:ls){
        for(auto enm:activeEnemies){
            if(bull->collidesWithItem(enm)){
                enemiesHealth[i] -= Hero.getDamage();
                points+=25;
                if(enemiesHealth[i]<=0){
                    points+=30;
                    ui->graphicsView->scene()->removeItem(activeEnemies.at(i));
                    enemiesHealth.erase(enemiesHealth.cbegin()+i);
                    activeEnemies.erase(activeEnemies.cbegin()+i);
                }
                return true;
            }
            i++;
        }
    }
    return false;
}

void sonerit::on_pushButton_clicked()
{
    if(gameInfo.size()==4){
        playerName1 = gameInfo.at(0);
        activeScene = stoi(gameInfo.at(1));
        points = stoi(gameInfo.at(3));
        saveRecord();
    }
    else if(gameInfo.size()==6){
        playerName1 = gameInfo.at(0);
        playerName2 = gameInfo.at(1);
        activeScene = stoi(gameInfo.at(2));
        points = stoi(gameInfo.at(3));
        saveRecord();
    }

    ui->label_player1_name->setText(ui->textEdit_player1->toPlainText()+" Health:");
    playerName1 = ui->textEdit_player1->toPlainText().toLocal8Bit().constData();
    heroHealth1 = Hero.getHealth();
    if(ui->checkBox->checkState()==Qt::Checked){
        secondHeroExists = true;
        ui->label_player2_name->setText(ui->textEdit_player2->toPlainText()+" Health:");
        playerName2 = ui->textEdit_player2->toPlainText().toLocal8Bit().constData();
        heroHealth2 = Hero.getHealth();
    }
    activeScene=0;
    points=0;

    changeScene();

    startGameTimers();

    ui->continue_button->~QPushButton();
    ui->pushButton->~QPushButton();
    ui->checkBox->~QCheckBox();
    checkStart->~QTimer();
    ui->textEdit_player1->~QPlainTextEdit();
    ui->textEdit_player2->~QPlainTextEdit();
    ui->label_2->~QLabel();
    ui->label_3->~QLabel();
}

void sonerit::createHero1Bullet()
{
    timerMov->stop();
    timerMov->start(10);
    qreal x=h1->x()+15, y=h1->y()+15;
    QGraphicsRectItem* temp = ui->graphicsView->scene()->addRect(0,0,30,30,QPen(Qt::transparent),Hero.getBrush());
    temp->setPos(x,y);
    hero1Bullet.push_front(temp);
    timerHB = new QTimer(this);
    timerHBe=true;
    if(direction1=='d') connect(timerHB,&QTimer::timeout,this,[=](){
        moveHeroBulletsDown(&hero1Bullet);
    });
    else if(direction1=='u') connect(timerHB,&QTimer::timeout,this,[=](){
        moveHeroBulletsUp(&hero1Bullet);
    });
    else if(direction1=='r') connect(timerHB,&QTimer::timeout,this,[=](){
        moveHeroBulletsRight(&hero1Bullet);
    });
    else if(direction1=='l') connect(timerHB,&QTimer::timeout,this,[=](){
        moveHeroBulletsLeft(&hero1Bullet);
    });
    timerHB->start(50);
}

void sonerit::createHero2Bullet()
{
    timerMov->stop();
    timerMov->start(10);
    qreal x=h2->x()+15, y=h2->y()+15;
    QGraphicsRectItem* temp = ui->graphicsView->scene()->addRect(0,0,30,30,QPen(Qt::transparent),Hero.getBrush());
    temp->setPos(x,y);
    hero2Bullet.push_front(temp);
    timer2HB = new QTimer(this);
    timer2HBe=true;
    if(direction1=='d') connect(timer2HB,&QTimer::timeout,this,[=](){
        moveHeroBulletsDown(&hero2Bullet);
    });
    else if(direction1=='u') connect(timer2HB,&QTimer::timeout,this,[=](){
        moveHeroBulletsUp(&hero2Bullet);
    });
    else if(direction1=='r') connect(timer2HB,&QTimer::timeout,this,[=](){
        moveHeroBulletsRight(&hero2Bullet);
    });
    else if(direction1=='l') connect(timer2HB,&QTimer::timeout,this,[=](){
        moveHeroBulletsLeft(&hero2Bullet);
    });
    timer2HB->start(50);
}

void sonerit::moveHeroBulletsRight(std::list<QGraphicsRectItem*>* ls)
{
    const int movSpeed = 15;
        for(auto bull:*ls){
            if(bullCollToEnm(*ls)||detectBulletCollision(ls)||bull->x()>=1200){
                ls->erase(ls->begin());
                if(ls==&hero1Bullet)
                    timerHB->stop();
                else if(ls==&hero2Bullet)
                    timer2HB->stop();
                ui->graphicsView->scene()->removeItem(bull);
                break;
            }
            else bull->setPos(bull->x()+movSpeed,bull->y());
        }
}

void sonerit::moveHeroBulletsLeft(std::list<QGraphicsRectItem*>* ls)
{
    const int movSpeed = 15;
        for(auto bull:*ls){
            if(bullCollToEnm(*ls)||detectBulletCollision(ls)||bull->x()<=50){
                ls->erase(ls->begin());
                if(ls==&hero1Bullet)
                    timerHB->stop();
                else if(ls==&hero2Bullet)
                    timer2HB->stop();
                ui->graphicsView->scene()->removeItem(bull);
                break;
            }
            else bull->setPos(bull->x()-movSpeed,bull->y());
        }
}

void sonerit::moveHeroBulletsUp(std::list<QGraphicsRectItem*>* ls)
{
    const int movSpeed = 15;
        for(auto bull:*ls){
            if(bullCollToEnm(*ls)||detectBulletCollision(ls)||bull->y()<=50){
                ls->erase(ls->begin());
                if(ls==&hero1Bullet)
                    timerHB->stop();
                else if(ls==&hero2Bullet)
                    timer2HB->stop();
                ui->graphicsView->scene()->removeItem(bull);
                break;
            }
            else bull->setPos(bull->x(),bull->y()-movSpeed);
        }
}

void sonerit::moveHeroBulletsDown(std::list<QGraphicsRectItem*>* ls)
{
    const int movSpeed = 15;
        for(auto bull:*ls){
            if(bullCollToEnm(*ls)||detectBulletCollision(ls)||bull->y()>=950){
                ls->erase(ls->begin());
                if(ls==&hero1Bullet)
                    timerHB->stop();
                else if(ls==&hero2Bullet)
                    timer2HB->stop();
                ui->graphicsView->scene()->removeItem(bull);
                break;
            }
            else bull->setPos(bull->x(),bull->y()+movSpeed);
        }
}

void sonerit::on_continue_button_clicked()
{
    loadGame();
    checkStart->~QTimer();
    ui->continue_button->~QPushButton();
    ui->pushButton->~QPushButton();
    ui->checkBox->~QCheckBox();
    ui->textEdit_player1->~QPlainTextEdit();
    ui->textEdit_player2->~QPlainTextEdit();
    ui->label_2->~QLabel();
    ui->label_3->~QLabel();
}

void sonerit::createHero(){
    h1XPOS=h1XPOS_O, h1YPOS=h1YPOS_O,h2XPOS=h2XPOS_O, h2YPOS=h2YPOS_O;
    h1 = ui->graphicsView->scene()->addRect(0,0,70,70,QPen(Qt::transparent),Qt::transparent);
    h1->setPos(h1XPOS,h1YPOS);
    heroS = new sprite();
    ui->graphicsView->scene()->addItem(heroS);
    heroS->setPos(h1XPOS,h1YPOS);
    if(secondHeroExists){
        h2 = ui->graphicsView->scene()->addRect(0,0,70,70,QPen(Qt::transparent),Qt::transparent);
        h2->setPos(h2XPOS,h2YPOS);
        heroS2 = new sprite();
        ui->graphicsView->scene()->addItem(heroS2);
        heroS2->setPos(h2XPOS,h2YPOS);
    }
}

void sonerit::checkStatus(){
    if(enemiesHealth.size()==0) changeScene();
    if(heroHealth1<=0){
        heroHealth1=0;
        h1->setEnabled(false);
        heroS->hide();
        if(!secondHeroExists){
            ui->label_gameover->setText("GAME OVER!");
            saveRecord();
            stopTimers();
        }
    }

    ui->lcd_health1->display(heroHealth1);
    if(secondHeroExists){
        if(heroHealth2<=0){
            heroHealth2=0;
            h2->setActive(false);
            heroS2->hide();
            if(!h1->isEnabled()){
                ui->label_gameover->setText("GAME OVER!");
                saveRecord();
                stopTimers();
            }
        }
        ui->lcd_health2->display(heroHealth2);
    }
    ui->lcd_points->display(points);
}

void sonerit::checkScndPly()
{
    if(ui->checkBox->isChecked()) ui->textEdit_player2->setDisabled(false);
    else ui->textEdit_player2->setDisabled(true);
}

void sonerit::loadGame()
{
    if(gameInfo.size()==6){
        playerName1 = gameInfo.at(0);
        playerName2 = gameInfo.at(1);
        ui->label_player1_name->setText(QString::fromStdString(playerName1)+" Health:");
        ui->label_player1_name->setText(QString::fromStdString(playerName2)+" Health:");
        activeScene = stoi(gameInfo.at(2));
        heroHealth1 = stoi(gameInfo.at(3));
        heroHealth2 = stoi(gameInfo.at(4));
        points = stoi(gameInfo.at(3));
        secondHeroExists = true;
        changeScene();
        startGameTimers();
    }
    else if(gameInfo.size()==4){
        playerName1 = gameInfo.at(0);
        activeScene = stoi(gameInfo.at(1));
        heroHealth1 = stoi(gameInfo.at(2));
        points = stoi(gameInfo.at(3));
        changeScene();
        startGameTimers();
    }
}

void sonerit::saveGame()
{
    std::string data;
    if(secondHeroExists){
        data = playerName1+','+playerName2+','+std::to_string(activeScene)+
                ','+std::to_string(heroHealth1)+','+std::to_string(heroHealth2)+
                ','+std::to_string(points)+';';
    }
    else{
        data = playerName1+','+std::to_string(activeScene)+
                ','+std::to_string(heroHealth1)+','+std::to_string(points)+';';
    }
    std::ofstream outFile;
    outFile.open(DATA);
    outFile << data;
    outFile.close();
}

void sonerit::saveRecord()
{
    std::vector<std::string> recordInfo {};
    std::ifstream inFile;
    inFile.open(RCRD);
    std::string data;
    while(1){
        inFile>>data;
        if(data=="!") break;
        recordInfo.push_back(data);
    }
    inFile.close();

    std::ofstream outFile;
    outFile.open(RCRD);
    if(secondHeroExists){
        data = playerName1+','+playerName2+','+std::to_string(activeScene)+
                ','+std::to_string(points);
    }
    else{
        data = playerName1+','+std::to_string(activeScene)+','+std::to_string(points);
    }
    for(unsigned long long g=0;g<=recordInfo.size();g++){
        if(g==0) outFile << data << std::endl;
        else{
            outFile << recordInfo.at(g-1) << std::endl;
        }
        if(g==recordInfo.size()) outFile << "!";
    }
    outFile.close();
}

void sonerit::startGameTimers()
{
    timerMov->start(10);
    timerEnemyMov->start(10);
    timerLive->start(15);
    timer->start(shootingTime);

}

void sonerit::stopTimers(){
    timer->stop();
    timerLive->stop();
    timerMov->stop();
    timerM->stop();
    if(timerHBe) timerHB->stop();
    if(timer2HBe) timer2HB->stop();
    timerEnemyMov->stop();
    timerTimeLeft->stop();
}

void sonerit::timerCount(){
    if(activeScene==5){
        ui->lcd_llt->display(lastLvlTime);
        lastLvlTime-=1;
        if(lastLvlTime==-1){
            ui->label_gameover->setText("GAME OVER!");
            saveRecord();
            stopTimers();
        }
    }
    timeLeft-=1;
    ui->lcd_time->display(timeLeft);
    if(timeLeft==0){
        timerTimeLeft->stop();
    }
}

#include "logic.h"
#include <QList>
#include <QByteArray>
#include <QHash>
#include <QStack>
#include <QFile>
#include <QTextStream>
#include <iostream>

struct Figure
{
  int type;
  int x;
  int y;
};

struct Step
{
  int fromX;
  int fromY;
  int toX;
  int toY;
};
struct Strike
{
    Figure figure;
    int step;
};

struct Logic::Impl
{
  QList<Figure> figures;
  QStack<Strike> strikes;
  QList<Step> steps;

  int findByPosition(int x, int y);
  bool move_possible(int type,int fromX, int fromY, int toX, int toY,bool strike);
  bool barier(int fromX, int fromY, int toX, int toY);
  bool move_back(int type,int fromX, int fromY, int toX, int toY,bool strike);
  int stepNumber=0;
};

int Logic::Impl::findByPosition(int x, int y) {
  for (int i(0); i<figures.size(); ++i) {
    if (figures[i].x != x || figures[i].y != y ) { 
      continue; 
    }
    return i;    
  }
  return -1;
}


Logic::Logic(QObject *parent)
  : QAbstractListModel(parent)
  , impl(new Impl()) 
{}

Logic::~Logic() {
}

int Logic::boardSize() const {
  return BOARD_SIZE;
}

bool Logic::get_startButton() const {

    return startButton;
}
void Logic::set_startButton(const bool &i){}
bool Logic::get_loadButton() const {

    return loadButton;
}
void Logic::set_loadButton(const bool &i){}
bool Logic::get_stopButton() const {

    return stopButton;
}
void Logic::set_stopButton(const bool &i){}
bool Logic::get_saveButton() const {

    return saveButton;
}
void Logic::set_saveButton(const bool &i){}
bool Logic::get_prevButton() const {

    return prevButton;
}
void Logic::set_prevButton(const bool &i){}
bool Logic::get_nextButton() const {

    return nextButton;
}
void Logic::set_nextButton(const bool &i){}

bool Logic::get_continueButton() const {

    return continueButton;
}
void Logic::set_continueButton(const bool &i){}
bool Logic::get_mouse() const {

    return mouse;
}
void Logic::set_mouse(const bool &i){}
bool Logic::get_game_over() const {

    return game_overText;
}
void Logic::set_game_over(const bool &i){}

int Logic::rowCount(const QModelIndex & ) const {
  return impl->figures.size(); 
}

QHash<int, QByteArray> Logic::roleNames() const { 
  QHash<int, QByteArray> names;
  names.insert(Roles::Type      , "type");
  names.insert(Roles::PositionX , "positionX");
  names.insert(Roles::PositionY , "positionY");
  return names;
}

QVariant Logic::data(const QModelIndex & modelIndex, int role) const { 
  if (!modelIndex.isValid()) {
    return QVariant();
  }
    
  int index = static_cast<int>(modelIndex.row());
  
  if (index >= impl->figures.size() || index < 0) {
    return QVariant();
  }

  Figure & figure = impl->figures[index];

  switch (role) {
    case Roles::Type     : return figure.type;
    case Roles::PositionX: return figure.x;
    case Roles::PositionY: return figure.y;
  }
  return QVariant(); 
}


void Logic::start() {
    clear();
    loadButton=false;
    emit loadButton_changed();
    startButton=false;
    emit startButton_changed();
    saveButton=true;
    emit saveButton_changed();
    stopButton=true;
    emit stopButton_changed();
    prevButton=false;
    emit prevButton_changed();
    nextButton=false;
    emit nextButton_changed();
    continueButton=false;
    emit continueButton_changed();
    mouse=true;
    emit mouse_changed();
    beginInsertRows(QModelIndex(), 0, 31);
      impl->figures << Figure { 2, 0, 0 };
      impl->figures << Figure { 4, 1, 0 };
      impl->figures << Figure { 6, 2, 0 };
      impl->figures << Figure { 8, 3, 0 };
      impl->figures << Figure { 10, 4, 0 };
      impl->figures << Figure { 6, 5, 0 };
      impl->figures << Figure { 4, 6, 0 };
      impl->figures << Figure { 2, 7, 0 };
      impl->figures << Figure { 0, 0, 1 };
      impl->figures << Figure { 0, 1, 1 };
      impl->figures << Figure { 0, 2, 1 };
      impl->figures << Figure { 0, 3, 1 };
      impl->figures << Figure { 0, 4, 1 };
      impl->figures << Figure { 0, 5, 1 };
      impl->figures << Figure { 0, 6, 1 };
      impl->figures << Figure { 0, 7, 1 };
      impl->figures << Figure { 3, 0, 7 };
      impl->figures << Figure { 5, 1, 7 };
      impl->figures << Figure { 7, 2, 7 };
      impl->figures << Figure { 9, 3, 7 };
      impl->figures << Figure { 11, 4, 7 };
      impl->figures << Figure { 7, 5, 7 };
      impl->figures << Figure { 5, 6, 7 };
      impl->figures << Figure { 3, 7, 7 };
      impl->figures << Figure { 1, 0, 6 };
      impl->figures << Figure { 1, 1, 6 };
      impl->figures << Figure { 1, 2, 6 };
      impl->figures << Figure { 1, 3, 6 };
      impl->figures << Figure { 1, 4, 6 };
      impl->figures << Figure { 1, 5, 6 };
      impl->figures << Figure { 1, 6, 6 };
      impl->figures << Figure { 1, 7, 6 };
    endInsertRows();


}
void Logic::load() {
    clear();
    prevButton=true;
    emit prevButton_changed();
    nextButton=true;
    emit nextButton_changed();
    continueButton=true;
    emit continueButton_changed();
    beginInsertRows(QModelIndex(), 0, 31);
      impl->figures << Figure { 2, 0, 0 };
      impl->figures << Figure { 4, 1, 0 };
      impl->figures << Figure { 6, 2, 0 };
      impl->figures << Figure { 8, 3, 0 };
      impl->figures << Figure { 10, 4, 0 };
      impl->figures << Figure { 6, 5, 0 };
      impl->figures << Figure { 4, 6, 0 };
      impl->figures << Figure { 2, 7, 0 };
      impl->figures << Figure { 0, 0, 1 };
      impl->figures << Figure { 0, 1, 1 };
      impl->figures << Figure { 0, 2, 1 };
      impl->figures << Figure { 0, 3, 1 };
      impl->figures << Figure { 0, 4, 1 };
      impl->figures << Figure { 0, 5, 1 };
      impl->figures << Figure { 0, 6, 1 };
      impl->figures << Figure { 0, 7, 1 };
      impl->figures << Figure { 3, 0, 7 };
      impl->figures << Figure { 5, 1, 7 };
      impl->figures << Figure { 7, 2, 7 };
      impl->figures << Figure { 9, 3, 7 };
      impl->figures << Figure { 11, 4, 7 };
      impl->figures << Figure { 7, 5, 7 };
      impl->figures << Figure { 5, 6, 7 };
      impl->figures << Figure { 3, 7, 7 };
      impl->figures << Figure { 1, 0, 6 };
      impl->figures << Figure { 1, 1, 6 };
      impl->figures << Figure { 1, 2, 6 };
      impl->figures << Figure { 1, 3, 6 };
      impl->figures << Figure { 1, 4, 6 };
      impl->figures << Figure { 1, 5, 6 };
      impl->figures << Figure { 1, 6, 6 };
      impl->figures << Figure { 1, 7, 6 };
    endInsertRows();

        static const char* const FILE_NAME = "game.txt";
        QFile in( FILE_NAME );
        if( in.open( QIODevice::ReadOnly ) ) {
            QTextStream stream( &in );
            int fromX;
            int fromY;
            int toX;
            int toY;
            while (!stream.atEnd()) {
                stream>>fromX;
                stream>>fromY;
                stream>>toX;
                stream>>toY;
                impl->steps << Step { fromX, fromY, toX, toY};
            }
            in.close();
        }
}

void Logic::stop() {
    mouse=false;
    emit mouse_changed();
    loadButton=true;
    emit loadButton_changed();
    startButton=true;
    emit startButton_changed();
    saveButton=false;
    emit saveButton_changed();
    stopButton=false;
    emit stopButton_changed();
  clear();
}

void Logic::clear() {
    beginResetModel();
      impl->figures.clear();
      impl->steps.clear();
    endResetModel();
    impl->stepNumber=0;
    game_overText=false;
    emit game_over_changed();
}

void Logic::game_over() {
   mouse=false;
   emit mouse_changed();
   game_overText=true;
   emit game_over_changed();
}

void Logic::save() {
    static const char* const FILE_NAME = "game.txt";
    QFile out( FILE_NAME );
    if( out.open( QIODevice::WriteOnly ) ) {
        QTextStream stream( &out );
        for(int i=0;i<impl->steps.size();i++)
        {
            stream<<impl->steps[i].fromX<<" "<<impl->steps[i].fromY<<" "<<impl->steps[i].toX<<" "<<impl->steps[i].toY<<" ";
        }
        out.close();
    }
}

void Logic::prev() {
    game_overText=false;
     emit game_over_changed();
     if(impl->stepNumber>0)
     {
         if(impl->strikes[impl->strikes.size()-1].step==impl->stepNumber-1)
             {
             beginInsertRows(QModelIndex(), impl->figures.size(), impl->figures.size());
                impl->figures<<impl->strikes.pop().figure;
             endInsertRows();
         }
         changePosition(impl->steps[impl->stepNumber-1].toX,impl->steps[impl->stepNumber-1].toY,impl->steps[impl->stepNumber-1].fromX,impl->steps[impl->stepNumber-1].fromY);
         impl->stepNumber--;
     }
}

bool Logic::next() {
     if(impl->stepNumber>=impl->steps.size()-1) return false;
         if (impl->findByPosition(impl->steps[impl->stepNumber].toX, impl->steps[impl->stepNumber].toY) >= 0) {
             if (impl->figures[impl->findByPosition(impl->steps[impl->stepNumber].toX, impl->steps[impl->stepNumber].toY)].type/2 == 5) game_over();
                 impl->strikes.push({impl->figures[impl->findByPosition(impl->steps[impl->stepNumber].toX, impl->steps[impl->stepNumber].toY)],impl->stepNumber});
                 del(impl->findByPosition(impl->steps[impl->stepNumber].toX, impl->steps[impl->stepNumber].toY));
         }
      changePosition(impl->steps[impl->stepNumber].fromX,impl->steps[impl->stepNumber].fromY,impl->steps[impl->stepNumber].toX,impl->steps[impl->stepNumber].toY);
      impl->stepNumber++;
     return true;
}

void Logic::cont() {
    mouse=true;
    emit mouse_changed();
    while (next()) {      }
    startButton=false;
    emit startButton_changed();
    stopButton=true;
    emit stopButton_changed();
    saveButton=true;
    emit saveButton_changed();
    loadButton=false;
    emit loadButton_changed();
    continueButton=false;
    prevButton=false;
    emit prevButton_changed();
    nextButton=false;
    emit nextButton_changed();
    continueButton=false;
    emit continueButton_changed();
    impl->stepNumber=impl->steps.size()-1;

}

void Logic::del(int row) {
    beginRemoveRows(QModelIndex(), row, row);
      impl->figures.takeAt(row);
            endRemoveRows();
        }


bool Logic::Impl::move_possible(int type,int fromX, int fromY, int toX, int toY,bool strike){
    switch (type/2) {
    case 0:
        return ((type-0.5)*(fromY-toY)==0.5*(1+(stepNumber/2==0)))||(((type-0.5)*(fromY-toY)==0.5)&&(abs(toX-fromX)==strike));
    case 1:
        return (toX-fromX)*(fromY-toY)==0;
    case 2:
        return (abs((toX-fromX)*(fromY-toY))==2)&&(abs(toX-fromX)+abs(fromY-toY)==3);
    case 3:
        return abs(toX-fromX)==abs(fromY-toY);
    case 4:
        return ((toX-fromX)*(fromY-toY)==0)||(abs(toX-fromX)==abs(fromY-toY));
    case 5:
        return (abs(toX-fromX)<=1)&&(abs(toY-fromY)<=1);

    default:
        break;
    }
}

bool Logic::Impl::barier(int fromX, int fromY, int toX, int toY){
    int x=toX-fromX==0?0:(toX-fromX)/abs(toX-fromX);
    int y=toY-fromY==0?0:(toY-fromY)/abs(toY-fromY);
    int max=abs(toX-fromX)>abs(toY-fromY)?abs(toX-fromX):abs(toY-fromY);
    int index;
    for(int i=1;i<max;i++)
    {
        index = findByPosition(fromX+i*x, fromY+i*y);
        if(index>=0) return true;
    }
    return false;
}


bool Logic::move(int fromX, int fromY, int toX, int toY) {
  int index = impl->findByPosition(fromX, fromY);
  if (index < 0) return false;
  if (impl->stepNumber%2!=impl->figures[index].type%2 ) return false;
  if (toX < 0 || toX >= BOARD_SIZE || toY < 0 || toY >= BOARD_SIZE ) {
    return false;
  }
  int index1 = impl->findByPosition(toX, toY);
  if (index1 >= 0) {
      if (!impl->move_possible(impl->figures[index].type,fromX, fromY, toX, toY,true) ) return false;
      if (((impl->figures[index].type/2==1)||(impl->figures[index].type/2==3)||(impl->figures[index].type/2==4))&&(impl->barier(fromX, fromY, toX, toY) )) return false;
      if (impl->figures[index1].type%2==impl->figures[index].type%2) {
        return false;
      }else{
          impl->strikes.push({impl->figures[index1],impl->stepNumber});
          if(impl->figures[index1].type/2==5)game_over();
          del(index1);
          if(index1<index) index--;
      }

  }else
  {
      if (!impl->move_possible(impl->figures[index].type,fromX, fromY, toX, toY,false) ) return false;
      if (((impl->figures[index].type/2==1)||(impl->figures[index].type/2==3)||(impl->figures[index].type/2==4))&&(impl->barier(fromX, fromY, toX, toY) )) return false;
  }
  impl->steps << Step { fromX, fromY, toX, toY};
  impl->stepNumber++;
  impl->figures[index].x = toX;
  impl->figures[index].y = toY;
  QModelIndex topLeft = createIndex(index, 0);
  QModelIndex bottomRight = createIndex(index, 0);
  emit dataChanged(topLeft, bottomRight);
  return true;
}


bool Logic::changePosition(int fromX, int fromY, int toX, int toY) {
  int index = impl->findByPosition(fromX, fromY);
  if (index < 0) return false;
  impl->figures[index].x = toX;
  impl->figures[index].y = toY;
  QModelIndex topLeft = createIndex(index, 0);
  QModelIndex bottomRight = createIndex(index, 0);
  emit dataChanged(topLeft, bottomRight);
  return true;
}

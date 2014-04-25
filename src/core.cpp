#include "core.h"

#include "tracker.h"

Core::Core()
  :currentGameMode(MODE_UNKNOWN)
{
  sceneManager.RegisterObserver(this);

  timer = new QTimer(this);
  connect(timer, SIGNAL(timeout()), this, SLOT(Tick()));
  timer->start(100);
}

Core::~Core() {
  delete timer;
}

void Core::Tick() {
  sceneManager.Update();
}

void Core::SceneChanged(Scene *oldScene, Scene *newScene) {
  // oldScene can be NULL
  if(oldScene) {
    cout << "OldScene " << oldScene->GetName() << " ";
  }
  cout << "NewScene " << newScene->GetName() << endl;

  if(newScene->GetName() ==  "Ingame") {
    if(oldScene->GetName() == "Constructed") {
      ConstructedScene *constructed = (ConstructedScene*)oldScene;
      currentGameMode = constructed->GetGameMode();
    }
  }

  if(oldScene && oldScene->GetName() == "Ingame") {
    IngameScene *ingame = (IngameScene*)oldScene;
    tracker.AddResult(currentGameMode,
        ingame->GetOutcome(),
        ingame->GetCoin(),
        ingame->GetOwnClass(),
        ingame->GetOpponentClass());
  }
}

#ifndef CALLBACK_H
#define CALLBACK_H

template <typename T> class ShowDetailsCallback {
  public:
    virtual void showDetails(T& entity) = 0;
};

template <typename T> class DeleteEntityCallback {
  public:
    virtual void deleteEntity(T& entity) = 0;
};

class CreateEntityCallback {
  public:
    virtual void createEntity() = 0;
};

class OpenLinkCallback {
  public:
    virtual void openLink() = 0;
};

#endif // CALLBACK_H

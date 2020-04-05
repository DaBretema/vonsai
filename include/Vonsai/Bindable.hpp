#pragma once

namespace Vonsai {

class Bindable {
public:
  virtual void bind() const   = 0;
  virtual void unbind() const = 0;
  virtual ~Bindable()         = default;
};

class BindGuard {
private:
  Bindable const *m_ptr = nullptr;

public:
  void inject(Bindable const *a_bindable);
  void inject(Bindable const &a_bindable);

  BindGuard();
  explicit BindGuard(Bindable const *a_bindable);
  explicit BindGuard(Bindable const &a_bindable);
  ~BindGuard();

  BindGuard(BindGuard &&) = delete;
  BindGuard &operator=(BindGuard &&) = delete;
  BindGuard(BindGuard const &)       = delete;
  BindGuard &operator=(BindGuard const &) = delete;
};

} // namespace Vonsai

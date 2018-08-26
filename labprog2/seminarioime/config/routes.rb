Rails.application.routes.draw do

  post 'interests', to: 'interests#create'
  delete 'interests', to: 'interests#destroy'
  devise_for :users, controllers: {
    sessions: 'users/sessions',
    registrations: 'users/registrations'
  }
  resources :groups
  resources :seminars, :except => :index

  get "/myarea/attendancelist", :to => 'area#attendance'
  get "/myarea/studentlist", :to => 'area#studentlist'
  get "/myarea/invite", :to => 'area#invite'
  get "/myarea/myseminars", :to => 'area#myseminars'

  post '/myarea/invite', to: 'area#create'

  post 'attendances', to: 'attendances#create'
  get 'attendances/new', to: 'attendances#new'
  get 'attendances/confirm/:rand_token', to: 'attendances#confirm_by_qr'

  get 'users/invite/:rand_token', to: 'invite#new', as: 'new_invite'

  post 'users/invite/:rand_token', to: 'invite#create', as: 'create_invite'

  post 'responsibilities', to: 'responsibilities#create'

  root to: "area#home"
end

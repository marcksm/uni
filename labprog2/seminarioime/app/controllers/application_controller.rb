class ApplicationController < ActionController::Base
  protect_from_forgery
  before_action :store_current_location, :unless => :devise_controller?
  
  private    
	  def store_current_location
	    store_location_for(:user, request.url)
	  end
end

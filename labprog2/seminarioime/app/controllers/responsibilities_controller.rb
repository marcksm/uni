class ResponsibilitiesController < ApplicationController

  def create
    return unless user_signed_in? && current_user.professor?
      
    @seminar = Seminar.find_by_id(params[:seminar_id])
    @user = User.find(params[:user_id])

    @responsibility = Responsibility.new
    @responsibility.user = @user
    @responsibility.seminar = @seminar
    @responsibility.save! if @responsibility.valid?
    
    redirect_to edit_seminar_path(id: @seminar.id)
  end 

end

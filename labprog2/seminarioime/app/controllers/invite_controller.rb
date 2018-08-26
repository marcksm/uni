class InviteController < ApplicationController

  def new
    @rand_string = SecureRandom.base58(60)
    @professor = Professor.find_by_token(params[:rand_token])

    @user = User.new()
    @user.email = @professor.email if @professor != nil
    @user.group_id = 1
    if @professor != nil
      if user_signed_in?
        flash[:notice] = "You must log off to register"
        redirect_to root_path and return
      end
      date_created = @professor.created_at.to_date
      date_today = Date.today.to_date
    else
      flash[:notice] = "Invite link invalid, expired or professor already registered"
      redirect_to root_path
    end
  end

  def create
    @form = params[:user]
    @link = request.base_url+"/users/invite/"+params[:rand_token]
    puts(@link)
    if @form[:nusp] == ""
      flash[:notice] = "NUSP can't be empty"
      redirect_to @link and return
    end
    if @form[:email] == ""
      flash[:notice] = "Email can't be empty"
      redirect_to @link and return
    end
    if @form[:name] == ""
      flash[:notice] = "Name can't be empty"
      redirect_to @link and return
    end
    if @form[:password] == "" || @form[:password].size <= 5
      flash[:notice] = "Password must have at least 6 characters"
      redirect_to @link and return
    end
    if @form[:password] != @form[:password_confirmation]
      flash[:notice] = "Password doesn't match"
      redirect_to @link and return
    end


    @user = User.new()
    @user.email = @form[:email]
    @user.name = @form[:name]
    @user.nusp = @form[:nusp]
    @user.usertype = true
    @user.group_id = @form[:group_id]
    @user.reset_password(@form[:password], @form[:password])

    Professor.find_by_email(@user.email).destroy!
    if @user.save!
      flash[:notice] = "Professor sucessfully registered"
      redirect_to '/'
    else
      puts @user.errors.to_yaml
    end
  end
end

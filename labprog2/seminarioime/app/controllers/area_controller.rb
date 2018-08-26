class AreaController < ApplicationController
  before_action :authenticate_user!, except: [:home]

  def invite
    if user_signed_in? && current_user.student?
      redirect_to root_path
      flash[:notice] = "Only logged professors can invite professors."
      return
    end
    @professors = Professor.new
  end

  def create
    @rand_string = SecureRandom.base58(60)
    if (User.find_by_email(professor_params) != nil)
      flash[:notice] = "Email already registered"
      redirect_to myarea_invite_path and return
    end
    if (Professor.find_by_email(professor_params) != nil)
      flash[:notice] = "Invite already sent"
      redirect_to myarea_invite_path and return
    end
    @professors = Professor.new(:email => professor_params, :token => @rand_string, :register => false)
    if user_signed_in? && current_user.professor?
      @professors.save
      @base = request.base_url
      if @base.include? "localhost"
        @iplocal = Socket.ip_address_list[1].ip_address
        @base = "http://"+@iplocal+":3000"
      end
      @reg_link = @base+"/users/invite/"+@rand_string
      UserNotifierMailer.send_email(@professors, @reg_link).deliver
      flash[:notice] = "You invited a new professor"
      redirect_to root_path
    end
  end

  def home
    if params[:search]
      @seminars = Seminar.where("name like ?", "%#{params[:search]}%")
    else @seminars = Seminar.all end

    if user_signed_in? && current_user.student?
      @interested = current_user.interests.map {|i| i.seminar}
      @seminars = @seminars.reject {|s| @interested.include? (s) }
    end
  end

  def attendance
    unless user_signed_in? && current_user.student?
      redirect_to action: "home"
      return
    end
    @user = current_user
    year = Date.today.year
    half_year = Date.new(year,7,20)

    if Date.new() > half_year
      interval = half_year..Date.new(year,12,-1)
    else
      interval = Date.new(year,1,1)..half_year
    end

    @attendences_in_semester = @user.attendances.where(updated_at: interval).count
  end

  def myseminars
    unless user_signed_in? && current_user.professor?
      redirect_to action: "home"
    end
    @seminars = current_user.mySeminars
  end

  def studentlist
    unless user_signed_in? && current_user.professor?
      redirect_to action: "home"
      return
    end
    if params[:search]
      @students = User.where("name like ?", "%#{params[:search]}%")
      @students = @students.select {|student| student.usertype == false}
    else @students = User.where(:usertype => false) end

  end
  private
  # Use callbacks to share common setup or constraints between actions.
    def professor_params
      params.require(:email)
    end
end

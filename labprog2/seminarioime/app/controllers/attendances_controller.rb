# coding: utf-8
class AttendancesController < ApplicationController
  before_action :authenticate_user!

  def new
    require 'rqrcode'
    require 'securerandom'

    @seminar = Seminar.find_by_id(params[:seminar_id])
    @responsibility = Responsibility.find_by(seminar_id: params[:seminar_id], user_id: current_user.id)

    unless @responsibility
      flash[:alert] = "You can`t confirm attendences in this seminar."
      redirect_to '/'
      return
    end
    attendance = Attendance.new
    @rand_string = SecureRandom.base58(60)
    attendance.responsibility_id = @responsibility.id
    attendance.random_string = @rand_string
    attendance.save

    @qr_link = request.base_url+"/attendances/confirm/"+@rand_string
    @qrcode = RQRCode::QRCode.new(@qr_link)
  end

  def create
    if params[:student_nusp].empty?
      flash[:notice] = "New QR Code generated"
    else
      flash[:alert] = confirm_attendence(params[:student_nusp], params[:rand_token])
      if flash[:alert] == nil
        username = User.find_by(nusp: params[:student_nusp]).name
        flash[:notice] = "Attendance confirmed for #{username} (NºUSP: #{params[:student_nusp]})"
      end
    end
    redirect_back fallback_location: root_path
    return
  end

  def confirm_by_qr
    result = confirm_attendence(current_user.nusp, params[:rand_token])
    if result.nil?
      attendance = Attendance.find_by(random_string: params[:rand_token])
      flash[:notice] = "Attendance confirmed for #{attendance.responsibility.seminar.name}"
    else
      flash[:alert] = result
    end
    redirect_to '/'
  end

  # Retorna uma memssagem falando se deu certo ou não. (retorna nill se não teve
  # nenhum erro)
  private
  def confirm_attendence (nusp, token)
    attendance = Attendance.find_by(random_string: token)
    user = User.find_by(nusp: nusp)

    # Verifica se token existe
    return "Invalid token." if !attendance

    # Verifica se não tem ninguem associado a esse token
    return "Token already used." if !attendance.user.nil?

    # Verifica se user existe
    return "User doesn't exist." if !user

    # Verifica se não é professor
    return "Only students need attendance confirmation." if user.professor?

    # Verifica se usuário ja tem presenca
    user_seminars = user.attendances.map do |user_attendence|
      user_attendence.responsibility.seminar_id
    end
    user_seminars.uniq!
    seminar_id = attendance.responsibility.seminar_id

    if user_seminars.include? seminar_id
      attendance.destroy
      return "Student already have attendance for this seminar"
    end

    # Confirma
    attendance.user = user
    attendance.save

    return nil
  end

end

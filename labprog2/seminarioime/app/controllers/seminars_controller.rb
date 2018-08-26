class SeminarsController < ApplicationController
  before_action :set_seminar, only: [:show, :edit, :update, :destroy]

  # GET /seminars/1
  # GET /seminars/1.json
  def show
    if user_signed_in? && current_user.student?
      @interest = Interest.find_by(seminar_id: @seminar.id,
                                   user_id: current_user.id)
    end

    @interest_count = Interest.where(seminar_id: @seminar.id).length
  end

  # GET /seminars/new
  def new
    unless user_signed_in? && current_user.professor?
      flash[:notice] = "Only logged Professors can create new seminars."
      redirect_to '/'
      return
    end

    @seminar = Seminar.new
  end

  # GET /seminars/1/edit
  def edit
    unless user_signed_in? && current_user.responsibilities.exists?(seminar_id: @seminar.id)
      flash[:notice] = "Only logged Professors can edit seminars."
      redirect_to '/'
      return
    end
  end

  # POST /seminars
  # POST /seminars.json
  def create
    unless user_signed_in? && current_user.professor?
      redirect_to '/'
      return
    end

    @seminar = Seminar.new(seminar_params)

    if @seminar.valid?
      respond_to do |format|
        if @seminar.save
          current_user.responsibilities.create!(seminar_id: @seminar.id)
          @users = User.all
          @users.each { |user|
            UserNotifierMailer.created_seminar(user, @seminar).deliver
          }
          format.html { redirect_to @seminar, notice: 'Seminar was successfully created.' }
          format.json { render :show, status: :created, location: @seminar }
        else
          format.html { render :new }
          format.json { render json: @seminar.errors, status: :unprocessable_entity }
        end
      end
    else
      @groups = Group.all.map {|group| [group.name, group.id]}
      render :new
    end
  end

  # PATCH/PUT /seminars/1
  # PATCH/PUT /seminars/1.json
  def update
    unless user_signed_in? && current_user.responsibilities.exists?(seminar_id: @seminar.id)
      redirect_to '/'
      return
    end

    respond_to do |format|
      if @seminar.update(seminar_params)

        @interests = @seminar.interests
        @interests.each { |interest|
          UserNotifierMailer.updated_seminar(interest.user, @seminar).deliver
        }
        format.html { redirect_to @seminar, notice: 'Seminar was successfully updated.' }
        format.json { render :show, status: :ok, location: @seminar }

      else
        format.html { render :edit }
        format.json { render json: @seminar.errors, status: :unprocessable_entity }
      end
    end

  end

  # DELETE /seminars/1
  # DELETE /seminars/1.json
  def destroy

    unless user_signed_in? && current_user.responsibilities.exists?(seminar_id: @seminar.id)
      redirect_to '/'
      return
    end

    if ( @seminar.attendances.size > 0)
      flash[:notice] = "You can't destroy this group. There are seminars or students in it."
      redirect_to '/'
      return
    end


    @seminar.destroy
    respond_to do |format|
      format.html { redirect_to '/', notice: 'Seminar was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_seminar
      @seminar = Seminar.find(params[:id])
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def seminar_params
      params.require(:seminar).permit(:seminar_id, :group_id, :name, :description, :place, :date)
    end
end

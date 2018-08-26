class GroupsController < ApplicationController
  before_action :authenticate_user!
  before_action :set_group, only: [:show, :edit, :update, :destroy]


  # GET /groups
  # GET /groups.json
  def index

    if params[:search]
      @groups = Group.where("name like ?", "%#{params[:search]}%")
    else @groups = Group.all end
  end

  # GET /groups/1
  # GET /groups/1.json
  def show
    @my_seminars = @group.seminars
    print (@group.users.size)
    print (@group.seminars.size)
  end

  # GET /groups/new
  def new
    if user_signed_in? && current_user.student?
      redirect_to action: "index"
      flash[:notice] = "Only logged Professors can create new groups."
      return
    end
    @group = Group.new
  end

  # GET /groups/1/edit
  def edit
    if user_signed_in? && current_user.student?
      redirect_to action: "index"
      flash[:notice] = "Only logged Professors can edit groups."
      return
    end
  end

  # POST /groups
  # POST /groups.json
  def create
    @group = Group.new(group_params)

    if not current_user.usertype
      respond_to do |format|
        format.html { redirect_to (@group) , notice: 'You dont have permission to create a group.' and return}
        format.json { render :show, status: :unprocessable_entity, location: @group }
      end
    end
    

    respond_to do |format|
      if @group.save
        format.html { redirect_to @group, notice: 'Group was successfully created.' }
        format.json { render :show, status: :created, location: @group }
      else
        format.html { render :new }
        format.json { render json: @group.errors, status: :unprocessable_entity }
      end
    end
  end

  # PATCH/PUT /groups/1
  # PATCH/PUT /groups/1.json
  def update
     
    if not current_user.usertype
      respond_to do |format|
        format.html { redirect_to groups_url , notice: 'You dont have permission to edit a group.' and return}
        format.json { render :show, status: :unprocessable_entity, location: @group }
      end
    end

    
    respond_to do |format|
      if @group.update(group_params)
        format.html { redirect_to @group, notice: 'Group was successfully updated.' }
        format.json { render :show, status: :ok, location: @group }
      else
        format.html { render :edit }
        format.json { render json: @group.errors, status: :unprocessable_entity }
      end
    end
  end

  # DELETE /groups/1
  # DELETE /groups/1.json
  def destroy
    if (@group.seminars.size > 0 or @group.users.size > 0)
      redirect_to action: "index"
      flash[:notice] = "You can't destroy this group. There are seminars or students in it."
      return
    end
    if not current_user.usertype
      respond_to do |format|
        format.html { redirect_to groups_url , notice: 'You dont have permission to remove a group.' and return}
        format.json { render :show, status: :unprocessable_entity, location: @group }
      end
    end
    @group.destroy
    respond_to do |format|
      format.html { redirect_to groups_url, notice: 'Group was successfully destroyed.' }
      format.json { head :no_content }
    end
  end

  private
    # Use callbacks to share common setup or constraints between actions.
    def set_group
      @group = Group.find(params[:id])
    end

    # Never trust parameters from the scary internet, only allow the white list through.
    def group_params
      params.require(:group).permit(:name)
    end
end

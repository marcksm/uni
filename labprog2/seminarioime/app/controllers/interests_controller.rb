class InterestsController < ApplicationController

    def create
        return unless user_signed_in? && current_user.student?

        @interest = Interest.new(seminar_id: params[:seminar_id],
                                 user_id: current_user.id)
        
        if @interest.valid?
            @interest.save!
        end

        redirect_to seminar_path(id: params[:seminar_id])
    end
    
    def destroy
        return unless user_signed_in? && current_user.student?
        
        @interest = Interest.find_by_id(params[:interest_id])
        @interest.destroy

        redirect_to seminar_path(id: @interest.seminar.id)
    end
    
    def interest_params 
        params.require(:interest).permit(:interest_id, :user_id, :seminar_id)
    end

end

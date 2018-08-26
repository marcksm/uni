class UserNotifierMailer < ApplicationMailer
	default :from => 'no-reply@seminario.melvans.com'

  	# send a signup email to the user, pass in the user object that   contains the user's email address
  	def send_email(user, link)
			@link = link
    	@user = user
    	mail( :to => @user.email,
    	:subject => 'SeminarioIME: complete your professor profile' )
  	end

  	def updated_seminar (user, seminar)
  		@user = user
  		@seminar = seminar

  		mail( :to => @user.email,
    	:subject => 'SeminarioIME: Hey! A Seminar you are interested in has been updated.' )
  	end

    def created_seminar (user, seminar)
      @user = user
      @seminar = seminar

      mail( :to => @user.email,
      :subject => 'There is a new seminar you can attend to.' )
    end
end

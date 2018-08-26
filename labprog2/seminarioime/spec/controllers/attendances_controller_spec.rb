require 'rails_helper'
require 'database_cleaner'
RSpec.describe AttendancesController do

 #Cappela:
    #Um aluno consegue confirmar por QR em um QR que já foi usado?

    before(:all) do
        DatabaseCleaner.start
        @group = Group.new
        @group.name = "teste_group"
        @group.save!

        @user_s = User.new
        @user_s.nusp = "123456"
        @user_s.name = "student"
        @user_s.password = "student"
        @user_s.email = "student@students.com"
        @user_s.group_id = @group.id
        @user_s.usertype = User.student
        @user_s.save!

        @user_s2 = User.new
        @user_s2.nusp = "234567"
        @user_s2.name = "student"
        @user_s2.password = "student"
        @user_s2.email = "student2@students.com"
        @user_s2.group_id = @group.id
        @user_s2.usertype = User.student
        @user_s2.save!

        @user_p1 = User.new
        @user_p1.nusp = "654321"
        @user_p1.name = "professor"
        @user_p1.password = "professor"
        @user_p1.email = "professor@professors.com"
        @user_p1.group_id = @group.id
        @user_p1.usertype = User.professor
        @user_p1.save!

        @user_p2 = User.new
        @user_p2.nusp = "765432"
        @user_p2.name = "professor"
        @user_p2.password = "professor"
        @user_p2.email = "professor2@professors.com"
        @user_p2.group_id = @group.id
        @user_p2.usertype = User.professor
        @user_p2.save!

        @user_p3 = User.new
        @user_p3.nusp = "876543"
        @user_p3.name = "professor"
        @user_p3.password = "professor"
        @user_p3.email = "professor3@professors.com"
        @user_p3.group_id = @group.id
        @user_p3.usertype = User.professor
        @user_p3.save!

        @seminar = Seminar.new
        @seminar.name = "Seminario_teste"
        @seminar.description = SecureRandom.base58(20)
        @seminar.place = SecureRandom.base58(10)
        @seminar.date = Date.new()
        @seminar.group_id = @group.id
        @seminar.save!

        @resp = Responsibility.new
        @resp.user = @user_p1
        @resp.seminar = @seminar
        @resp.save!

        @resp2 = Responsibility.new
        @resp2.user = @user_p3
        @resp2.seminar = @seminar
        @resp2.save!
    end

    after(:all) do
        DatabaseCleaner.clean
    end

    before(:each) do
        @request.env["devise.mapping"] = Devise.mappings[:user]
    end

    context 'when rendering' do
      it 'should render new attendance page if requested by professor with responsability' do
        sign_in @user_p1
        get :new, params: {:seminar_id => @seminar.id}
        expect(response).to render_template ("new")
      end

      it 'should not render new attendance page if requested by professor without responsability' do
        sign_in @user_p2
        get :new, params: {:seminar_id => @seminar.id}
        expect(response).not_to render_template ("new")
      end

      it 'should not render new attendance page if requested by student' do
        sign_in @user_s
        get :new, params: {:seminar_id => @seminar.id}
        expect(response).not_to render_template ("new")
      end

      it 'should not render new attendance page if user is not logged' do
        get :new, params: {:seminar_id => @seminar.id}
        expect(response).not_to render_template ("new")
      end
    end

    context 'when confirming by nusp' do

      before (:each) {
          @user_s.attendances.each { |a| a.delete }
          @user_s2.attendances.each { |a| a.delete }
          @user_s.reload
          @user_s2.reload
      }

      it 'should confirm if user not yet confirmed in this seminar and nusp is a valid student nusp and token is valid' do
        sign_in @user_p1
        get :new, params: {:seminar_id => @seminar.id}
        post :create, params: {:student_nusp => @user_s.nusp, :rand_token => assigns(:rand_string)}
        expect(@user_s.attendances.size).to be_equal (1)
      end

      it 'should confirm if user nusp not valid and token is valid' do
        sign_in @user_p1
        get :new, params: {:seminar_id => @seminar.id}
        expect {
            post :create, params: {:student_nusp => 12323454, :rand_token => assigns(:rand_string)}
        }.to change(Attendance, :count).by(0)
      end

      it 'should not confirm for student already confirmed in this seminar (by the same professor)' do
        sign_in @user_p1
        get :new, params: {:seminar_id => @seminar.id}
        post :create, params: {:student_nusp => @user_s.nusp, :rand_token => assigns(:rand_string)}

        get :new, params: {:seminar_id => @seminar.id}
        post :create, params: {:student_nusp => @user_s.nusp, :rand_token => assigns(:rand_string)}
        expect(@user_s.attendances.size).to be_equal (1)
      end
      it 'should not confirm for student already confirmed in this seminar (by a different professor)' do
        sign_in @user_p1
        get :new, params: {:seminar_id => @seminar.id}
        post :create, params: {:student_nusp => @user_s.nusp, :rand_token => assigns(:rand_string)}

        sign_out @user_p1
        sign_in @user_p3
        get :new, params: {:seminar_id => @seminar.id}
        post :create, params: {:student_nusp => @user_s.nusp, :rand_token => assigns(:rand_string)}
        expect(@user_s.attendances.size).to be_equal (1)
      end
      it 'should not confirm if professor is not responsible for the seminar' do
        sign_in @user_p2
        get :new, params: {:seminar_id => @seminar.id}
        post :create, params: {:student_nusp => @user_s.nusp, :rand_token => assigns(:rand_string)}
        expect(@user_s.attendances.size).to be_equal (0)
      end
      it 'should not confirm if token was already used' do
        sign_in @user_p1
        get :new, params: {:seminar_id => @seminar.id}
        token = assigns(:rand_string)
        post :create, params: {:student_nusp => @user_s.nusp, :rand_token => token}
        expect(@user_s.attendances.size).to be_equal (1)
        post :create, params: {:student_nusp => @user_s2.nusp, :rand_token => token}
        expect(@user_s2.attendances.size).to be_equal (0)
      end
      it 'should not confirm if token is invalid' do
        sign_in @user_p1
        get :new, params: {:seminar_id => @seminar.id}
        post :create, params: {:student_nusp => @user_s.nusp, :rand_token => "invalid_token"}
        expect(@user_s.attendances.size).to be_equal (0)
      end
    end

    context 'when confirming by qr code' do
        it 'should confirm if everything is correct' do
            sign_in @user_p1
            get :new, params: {:seminar_id => @seminar.id}
            token = assigns(:rand_string)
            sign_out @user_p1
            sign_in @user_s
            expect {
                post :confirm_by_qr, params: {:rand_token => token}
                @user_s.attendances.reload
            }.to change(@user_s.attendances, :count).by(1)
        end

        it 'should not confirm the same token' do
            sign_in @user_p1
            get :new, params: {:seminar_id => @seminar.id}
            token = assigns(:rand_string)
            sign_out @user_p1
            sign_in @user_s
            post :confirm_by_qr, params: {:rand_token => token}
            expect {
                post :confirm_by_qr, params: {:rand_token => token}
            }.to change(Attendance, :count).by(0)
        end

        it 'should not confirm in the same seminar by two diferents tokens' do
            sign_in @user_p1
            get :new, params: {:seminar_id => @seminar.id}
            token1 = assigns(:rand_string)
            get :new, params: {:seminar_id => @seminar.id}
            token2 = assigns(:rand_string)
            sign_out @user_p1
            sign_in @user_s
            expect {
                post :confirm_by_qr, params: {:rand_token => token1}
                @user_s.attendances.reload
            }.to change(@user_s.attendances, :count).by(1)
            expect {
                post :confirm_by_qr, params: {:rand_token => token2}
                @user_s.attendances.reload
            }.to change(@user_s.attendances, :count).by(0)
        end

        it 'should be redirect if not login' do
            sign_in @user_p1
            get :new, params: {:seminar_id => @seminar.id}
            token = assigns(:rand_string)
            sign_out @user_p1
            post :confirm_by_qr, params: {:rand_token => token}
            assert_response :redirect
        end

        it 'should not confirm if the qr is already used by other user' do
            sign_in @user_p1
            get :new, params: {:seminar_id => @seminar.id}
            token = assigns(:rand_string)
            sign_out @user_p1

            sign_in @user_s
            expect {
                post :confirm_by_qr, params: {:rand_token => token}
                @user_s.attendances.reload
            }.to change(@user_s.attendances, :count).by(1)
            sign_out @user_s

            sign_in @user_s2
            expect {
                post :confirm_by_qr, params: {:rand_token => token}
                @user_s2.attendances.reload
            }.to change(@user_s2.attendances, :count).by(0)
        end
    end

end

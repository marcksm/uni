require 'rails_helper'
require 'database_cleaner'
RSpec.describe AreaController do

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

        @user_p = User.new
        @user_p.nusp = "654321"
        @user_p.name = "professor"
        @user_p.password = "professor"
        @user_p.email = "professor@professors.com"
        @user_p.group_id = @group.id
        @user_p.usertype = User.professor
        @user_p.save!
    end

    after(:all) do
        DatabaseCleaner.clean
    end

    before(:each) do
        @request.env["devise.mapping"] = Devise.mappings[:user]
    end

    context 'myarea' do

      it 'shouldn\'t access my attendance list if user or professor not logged in' do
        get :attendance
        assert_response :redirect
      end
      it 'should access my attendance list if user logged in' do
        sign_in @user_s
        get :attendance
        assert_response :success
      end
      it 'shouldn\'t access my attendance list if a professor is logged in' do
        sign_in @user_p
        get :attendance
        assert_response :redirect
      end




      it 'shouldn\'t access my student list if user or professor not logged in' do
        get :studentlist
        assert_response :redirect
      end

      it 'should access my attendance list if professsor logged in' do
        sign_in @user_p
        get :studentlist
        assert_response :success
      end

      it 'shouldn\'t access my student list if a student is logged in' do
        sign_in @user_s
        get :studentlist
        assert_response :redirect
      end



    end
end

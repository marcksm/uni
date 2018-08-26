require 'rails_helper'

RSpec.describe ResponsibilitiesController, type: :controller do
    before(:all) do
        DatabaseCleaner.start
        @group = Group.new
        @group.name = "teste_group"
        @group.save!
        
        @seminar = Seminar.new
        @seminar.name = "teste_seminar"
        @seminar.group_id = @group.id
        @seminar.description = SecureRandom.base58(20)
        @seminar.place = SecureRandom.base58(10)
        @seminar.date = Date.new()
        @seminar.save!

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

        @user_p2 = User.new
        @user_p2.nusp = "222222"
        @user_p2.name = "professor2"
        @user_p2.password = "professor2"
        @user_p2.email = "professor2@professors.com"
        @user_p2.group_id = @group.id
        @user_p2.usertype = User.professor
        @user_p2.save!

        @responsibility = Responsibility.new
        @responsibility.user_id = @user_p.id
        @responsibility.seminar_id = @seminar.id
        @responsibility.save!
    end
    
    after(:all) do
        DatabaseCleaner.clean
    end

    before(:each) do
        @request.env["devise.mapping"] = Devise.mappings[:user]
    end

    context "when creating a new responsibility" do

      it 'should create if conditions are normal' do
        sign_in @user_p
        expect {
          post :create, params: {user_id: @user_p2.id, seminar_id: @seminar.id}
        }.to change(Responsibility, :count).by(1)
      end
 
      it 'shouldn\'t create if user is not logged in' do
        expect {
          post :create, params: {user_id: @user_p2.id, seminar_id: @seminar.id}
        }.to change(Responsibility, :count).by(0)
      end

      it 'shouldn\'t create if user is a student' do
        sign_in @user_s
        expect {
          post :create, params: {user_id: @user_p2.id, seminar_id: @seminar.id}
        }.to change(Responsibility, :count).by(0)
      end

      it 'shouldn\'t create if responsibility already exists' do
        @responsibility = Responsibility.new
        @responsibility.seminar = @seminar
        @responsibility.user = @user_p2
        @responsibility.save

        sign_in @user_p
        expect {
          post :create, params: {user_id: @user_p2.id, seminar_id: @seminar.id}
        }.to change(Responsibility, :count).by(0)
      end
   end
end

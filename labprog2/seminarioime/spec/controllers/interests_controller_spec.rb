require 'rails_helper'

RSpec.describe InterestsController, type: :controller do
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
    end
    
    after(:all) do
        DatabaseCleaner.clean
    end

    before(:each) do
        @request.env["devise.mapping"] = Devise.mappings[:user]
    end

    context "when creating a new interest" do
        
        it 'should create if conditions are normal' do 
            sign_in @user_s
            expect {
                post :create, params: {seminar_id: @seminar.id}
            }.to change(Interest, :count).by(1)
        end
       
        it 'shouldn\'t create if user not logged' do
            expect {
                post :create, params: {seminar_id: @seminar.id}
            }.to change(Interest, :count).by(0)
        end

        it 'shouldn\'t create if user is a professor' do
            sign_in @user_p
            expect {
                post :create, params: {seminar_id: @seminar.id}
            }.to change(Interest, :count).by(0)
        end

        it 'shouldn\'t create if interest already exists' do
            @interest = Interest.new
            @interest.seminar = @seminar
            @interest.user = @user_s
            @interest.save
            
            sign_in @user_s
            expect {
                post :create, params: {seminar_id: @seminar.id}
            }.to change(Interest, :count).by(0)
        end
        
    end
    
    context 'when deleting an interest' do

        before(:each) do
            @interest = Interest.new
            @interest.seminar = @seminar
            @interest.user = @user_s
            @interest.save
        end

        it 'shouldn\'t delete if user not logged' do
            expect {
                delete :destroy, params: {interest_id: @interest.id}
            }.to change(Interest, :count).by(0)
        end

        it 'shouldn\'t delete if user is a professor' do
            sign_in @user_p
            expect {
                delete :destroy, params: {interest_id: @interest.id}
            }.to change(Interest, :count).by(0)
        end

        it 'should delete if conditions are normal' do
            sign_in @user_s
            expect {
                delete :destroy, params: {interest_id: @interest.id}
            }.to change(Interest, :count).by(-1)
        end

    end

end

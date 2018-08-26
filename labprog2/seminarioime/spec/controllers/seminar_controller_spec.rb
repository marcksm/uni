require 'rails_helper'
require 'database_cleaner'

RSpec.describe SeminarsController do

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


    context 'when creating a new seminar' do

        it 'shouldn\'t show page if user is not logged' do
            get :new
            assert_response :redirect
        end

        it 'shouldn\'t show page if user is a student' do
            sign_in @user_s
            get :new
            assert_response :redirect
        end

        it 'should show page if user is a professor' do
            sign_in @user_p
            get :new
            assert_response :success
        end

        it 'shouldn\'t create if user not logged' do
            expect {
                post :create, params: {seminar: {
                    group_id: @group.id,
                    name: "teste_seminar3",
                    description: SecureRandom.base58(20),
                    place: SecureRandom.base58(10),
                    date: Date.new()
                }}
            }.to change(Seminar, :count).by(0)
        end

        it 'shouldn\'t create if user is a student' do
            sign_in @user_s
            expect {
                post :create, params: {seminar: {
                    group_id: @group.id,
                    name: "teste_seminar3",
                    description: SecureRandom.base58(20),
                    place: SecureRandom.base58(10),
                    date: Date.new()
                }}
            }.to change(Seminar, :count).by(0)
        end

        it 'should create if user is a professor and seminar\'s name is unique' do
            sign_in @user_p
            expect {
                post :create, params: {seminar: {
                    group_id: @group.id,
                    name: "teste_seminar3",
                    description: SecureRandom.base58(20),
                    place: SecureRandom.base58(10),
                    date: Date.new()
                }}
            }.to change(Seminar, :count).by(1)

        end

        it 'shouldn\'t create if name already exists' do
            @seminar = Seminar.new
            @seminar.name = "teste_seminar"
            @seminar.group_id = @group.id
            @seminar.description = SecureRandom.base58(20)
            @seminar.place = SecureRandom.base58(10)
            @seminar.date = Date.new()
            @seminar.save!

            sign_in @user_p
            expect {
                post :create, params: {seminar: {group_id: @group.id, name: "teste_seminar"}}
            }.to change(Seminar, :count).by(0)
        end
    end

    context 'when deleting a seminar' do

        before(:each) do
            @seminar = Seminar.new
            @seminar.name = "teste_seminar"
            @seminar.group_id = @group.id
            @seminar.description = SecureRandom.base58(20)
            @seminar.place = SecureRandom.base58(10)
            @seminar.date = Date.new()
            @seminar.save!
        end

        it 'shouldn\'t delete if user not logged' do
            expect {
                delete :destroy, params: {id: @seminar.to_param}
            }.to change(Seminar, :count).by(0)
        end

        it 'shouldn\'t delete if user is a student' do
            sign_in @user_s
            expect {
                delete :destroy, params: {id: @seminar.to_param}
            }.to change(Seminar, :count).by(0)
        end

        it 'should delete if user is a professor and has responsibility of this seminar' do
            @responsibility = Responsibility.new
            @responsibility.user = @user_p
            @responsibility.seminar = @seminar
            @responsibility.save!

            @seminar.responsibilities << @responsibility
            @seminar.save!

            sign_in @user_p
            expect {
                delete :destroy, params: {id: @seminar.to_param}
            }.to change(Seminar, :count).by(-1)
        end

        it 'should not delete if user is a professor and has not responsibility of this seminar' do
            sign_in @user_p
            expect {
                delete :destroy, params: {id: @seminar.to_param}
            }.to change(Seminar, :count).by(0)
        end

    end

    context 'when updating a seminar' do

        before(:each) do
            @seminar = Seminar.new
            @seminar.name = "teste_seminar"
            @seminar.group_id = @group.id
            @seminar.description = SecureRandom.base58(20)
            @seminar.place = SecureRandom.base58(10)
            @seminar.date = Date.new()
            @seminar.save!
            @seminarid = @seminar.id
        end

        it 'shouldn\'t show page if user is not logged' do
            get :edit, params: {id: @seminar.to_param}
            assert_response :redirect
        end

        it 'shouldn\'t show page if user is a student' do
            sign_in @user_s
            get :edit, params: {id: @seminar.to_param}
            assert_response :redirect
        end

        it 'should show page if user is a professor with responsibility for the seminar' do
            @responsibility = Responsibility.new
            @responsibility.user = @user_p
            @responsibility.seminar = @seminar
            @responsibility.save!

            @seminar.responsibilities << @responsibility
            @seminar.save!
            
            sign_in @user_p
            get :edit, params: {id: @seminar.to_param}
            assert_response :success
        end

        it 'shouldn\'t show page if user is a professor with no responsibility for the seminar' do
            sign_in @user_p
            get :edit, params: {id: @seminar.to_param}
            assert_response :redirect
        end

        it 'shouldn\'t update if user not logged' do
            sname = @seminar.name
            put :update, params: {id: @seminar.to_param, seminar: {name: "teste_seminar2"}}
            @seminar = Seminar.find @seminarid
            expect(@seminar.name).to eq(sname)
        end

        it 'shouldn\'t update if user is a student' do
            sign_in @user_s
            sname = @seminar.name
            put :update, params: {id: @seminar.to_param, seminar: {name: "teste_seminar2"}}
            @seminar = Seminar.find @seminarid
            expect(@seminar.name).to eq(sname)
        end

        it 'should update if user is a professor that has responsibility for the seminar and it\'s name is unique' do
            @responsibility = Responsibility.new
            @responsibility.user = @user_p
            @responsibility.seminar = @seminar
            @responsibility.save!

            @seminar.responsibilities << @responsibility
            @seminar.save!

            sign_in @user_p
            new_name = "teste_seminar2"
            put :update, params: {id: @seminar.to_param, seminar: {name: new_name}}
            @seminar = Seminar.find @seminarid
            expect(@seminar.name).to eq(new_name)
        end

        it 'shouldn\'t update if user is a professor that has responsibility for the seminar and it\'s name is not unique' do
            @responsibility = Responsibility.new
            @responsibility.user = @user_p
            @responsibility.seminar = @seminar
            @responsibility.save!

            @seminar.responsibilities << @responsibility
            @seminar.save!

            seminar2 = Seminar.new
            seminar2.name = "teste_seminar2"
            seminar2.group_id = @group.id
            seminar2.description = SecureRandom.base58(20)
            seminar2.place = SecureRandom.base58(10)
            seminar2.date = Date.new()
            seminar2.save!

            sign_in @user_p
            sname = @seminar.name
            put :update, params: {id: @seminar.to_param, seminar: {name: seminar2.name}}
            @seminar = Seminar.find @seminarid
            expect(@seminar.name).to eq(sname)
        end

        it 'shouldn\'t update if user is a professor with no responsibility for the seminar' do
            sign_in @user_p
            sname = @seminar.name
            put :update, params: {id: @seminar.to_param, seminar: {name: "teste_seminar2"}}
            @seminar = Seminar.find @seminarid
            expect(@seminar.name).to eq(sname)
        end

    end

end

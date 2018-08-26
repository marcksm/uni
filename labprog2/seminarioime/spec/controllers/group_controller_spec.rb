require 'rails_helper'
require 'database_cleaner'

RSpec.describe GroupsController do

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


    context 'when creating a new group' do

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
                post :create, params: {group: {name: "teste_group3"}}
            }.to change(Group, :count).by(0)
        end

        it 'shouldn\'t create if user is a student' do
            sign_in @user_s
            expect {
                post :create, params: {group: {name: "teste_group3"}}
            }.to change(Group, :count).by(0)
        end

        it 'should create if user is a professor' do
            sign_in @user_p
            expect {
                post :create, params: {group: {name: "teste_group3"}}
            }.to change(Group, :count).by(1)

        end

        it 'shouldn\'t create if name already exists' do
            sign_in @user_p
            expect {
                post :create, params: {group: {name: "teste_group"}}
            }.to change(Group, :count).by(0)

        end

    end

    context 'when deleting a group' do

        before(:each) do
            @group2 = Group.new
            @group2.name = "teste_group2"
            @group2.save!
        end

        it 'shouldn\'t delete if user not logged' do
            expect {
                delete :destroy, params: {id: @group2.to_param}
            }.to change(Group, :count).by(0)
        end

        it 'shouldn\'t delete if user is a student' do
            sign_in @user_s
            expect {
                delete :destroy, params: {id: @group2.to_param}
            }.to change(Group, :count).by(0)
        end

        it 'should delete if user is a professor and group is empty' do
            sign_in @user_p
            expect {
                delete :destroy, params: {id: @group2.to_param}
            }.to change(Group, :count).by(-1)

        end

        it 'shouldn\'t delete group if there is at least a user in it' do
            sign_in @user_p
            expect {
                delete :destroy, params: {id: @group.to_param}
            }.to change(Group, :count).by(0)
        end

        it 'shouldn\'t delete group if there is at least a seminar in it' do

            @seminar = Seminar.new
            @seminar.name = "teste_seminar"
            @seminar.group_id = @group2.id
            @seminar.description = SecureRandom.base58(20)
            @seminar.place = SecureRandom.base58(10)
            @seminar.date = Date.new()
            @seminar.save!

            sign_in @user_p
            expect {
                delete :destroy, params: {id: @group2.to_param}
            }.to change(Group, :count).by(0)

        end

    end

    context 'when updating a group' do

        before(:each) do
            @group2 = Group.new
            @group2.name = "teste_group2"
            @group2.save!
            @group2id = @group2.id
        end

        it 'shouldn\'t show page if user is not logged' do
            get :edit, params: {id: @group2.to_param}
            assert_response :redirect
        end

        it 'shouldn\'t show page if user is a student' do
            sign_in @user_s
            get :edit, params: {id: @group2.to_param}
            assert_response :redirect
        end

        it 'should show page if user is a professor' do
            sign_in @user_p
            get :edit, params: {id: @group2.to_param}
            assert_response :success
        end


        it 'shouldn\'t update if user not logged' do
            gname = @group2.name
            put :update, params: {id: @group2.to_param, group: {name: "teste_group4"}}
            @group2 = Group.find @group2id
            expect(@group2.name).to eq(gname)
        end

        it 'shouldn\'t update if user is a student' do
            sign_in @user_s
            gname = @group2.name
            put :update, params: {id: @group2.to_param, group: {name: "teste_group4"}}
            @group2 = Group.find @group2id
            expect(@group2.name).to eq(gname)
        end

        it 'should update if user is a professor and group name is unique' do
            sign_in @user_p
            new_name = "teste_group4"
            put :update, params: {id: @group2.to_param, group: {name: new_name}}
            @group2 = Group.find @group2id
            expect(@group2.name).to eq(new_name)
        end

        it 'shouldn\'t update if user is a professor and group name isn\'t unique' do
            sign_in @user_p
            gname = @group2.name
            put :update, params: {id: @group2.to_param, group: {name: @group.name}}
            @group2 = Group.find @group2id
            expect(@group2.name).to eq(gname)

        end

    end

end

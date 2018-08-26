require 'rails_helper'

RSpec.describe Responsibility, type: :model do
    
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
    
    it "is valid with valid attributes" do
      expect(Responsibility.new(seminar_id: @seminar.id, user_id: @user_p.id)).to be_valid
    end
    
    it "is not valid without a user" do 
      expect(Responsibility.new(seminar_id: @seminar.id)).to be_invalid
    end
    
    it "is not valid without a seminar" do 
      expect(Responsibility.new(user_id: @user_p.id)).to be_invalid
    end
    
    it "is not valid when user is taken" do 
      @responsibility = Responsibility.new
      @responsibility.seminar = @seminar
      @responsibility.user = @user_p
      @responsibility.save

      expect(Responsibility.new(seminar_id: @seminar.id, user_id: @user_p.id)).to be_invalid
    end
end

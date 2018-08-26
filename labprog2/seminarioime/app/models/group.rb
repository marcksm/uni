class Group < ApplicationRecord
  validates :name, uniqueness: true, presence: true
  has_many :seminars
  has_many :users
end

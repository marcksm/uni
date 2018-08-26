class Seminar < ApplicationRecord
  belongs_to :group
  has_many :responsibilities
  has_many :users, through: :responsibilities
  has_many :attendances, through: :responsibilities
  has_many :interests

  validates :name, uniqueness: :true, presence: true
  validates :date, presence: true, :allow_blank => false
  validates :place, presence: true, :allow_blank => false
  validates_length_of :description, :minimum => 20, :allow_blank => false

end

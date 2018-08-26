class User < ApplicationRecord
  # Include default devise modules. Others available are:
  # :confirmable, :lockable, :timeoutable and :omniauthable
  devise :database_authenticatable, :registerable,
         :recoverable, :rememberable, :trackable, :validatable
  belongs_to :group
  has_many :responsibilities
  has_many :seminars, through: :responsibilities
  has_many :attendances
  has_many :interests

  validates :nusp, presence: true, allow_blank: false, uniqueness: true
  validates :name, presence: true, allow_blank: false


  accepts_nested_attributes_for :group

  def professor?
    self.usertype
  end

  def student?
    !self.usertype
  end

  def self.student
    return false
  end

  def self.professor
    return true
  end

  def attendedSeminars
    if self.student?
      self.attendances.map{ |attendance|
        attendance.responsibility.seminar }
    end
  end

  def mySeminars
    if self.professor?
      self.responsibilities.map{ |responsibility|
        responsibility.seminar }      
    end
  end
end
